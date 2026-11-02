/* GS memory addressing and texture decoding, on synthetic VRAM. */
#include "check.h"
#include "gs_regs.h"
#include "gs_vram.h"

#include <stdlib.h>
#include <string.h>

/* Every pixel of one page lands on its own storage unit inside that page. */
static void check_page(unsigned psm, int w, int h)
{
    unsigned bpp = gs_psm_bpp(psm);
    uint8_t *seen = calloc(8192 * 2, 1);
    int distinct = 1, inside = 1;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            unsigned nibble;
            uint32_t off = gs_vram_offset(0, 2, psm, x, y, &nibble);
            if (off >= 8192 || (bpp >= 16 && off % (bpp == 16 ? 2 : 4)))
                inside = 0;
            else {
                uint32_t unit = bpp == 4 ? off * 2 + nibble : off;
                if (seen[unit])
                    distinct = 0;
                seen[unit] = 1;
            }
        }
    CHECK(inside);
    CHECK(distinct);
    free(seen);
}

static uint32_t next_random(uint32_t *s)
{
    *s = *s * 1664525u + 1013904223u;
    return *s >> 8;
}

/* Writes then reads back a 128x128 area for one mode. */
static void check_roundtrip(uint8_t *vram, unsigned psm)
{
    unsigned bpp = gs_psm_bpp(psm);
    uint32_t mask = bpp == 32 ? 0xFFFFFFFFu : (1u << bpp) - 1;
    uint32_t s = psm + 1;
    memset(vram, 0, GS_VRAM_SIZE);
    for (int y = 0; y < 128; y++)
        for (int x = 0; x < 128; x++)
            gs_vram_write(vram, 0x40, 2, psm, x, y, next_random(&s) * 2654435761u);
    s = psm + 1;
    int ok = 1;
    for (int y = 0; y < 128; y++)
        for (int x = 0; x < 128; x++)
            if (gs_vram_read(vram, 0x40, 2, psm, x, y) != ((next_random(&s) * 2654435761u) & mask))
                ok = 0;
    if (!ok)
        fprintf(stderr, "round trip failed for psm 0x%02X\n", psm);
    CHECK(ok);
}

int main(void)
{
    uint8_t *vram = calloc(1, GS_VRAM_SIZE);
    if (!vram)
        return 1;

    CHECK_EQ(gs_psm_bpp(GS_PSMCT32), 32u);
    CHECK_EQ(gs_psm_bpp(GS_PSMCT24), 24u);
    CHECK_EQ(gs_psm_bpp(GS_PSMCT16S), 16u);
    CHECK_EQ(gs_psm_bpp(GS_PSMT8H), 8u);
    CHECK_EQ(gs_psm_bpp(GS_PSMT4HH), 4u);
    CHECK_EQ(gs_psm_bpp(GS_PSMZ16), 16u);
    CHECK(!gs_psm_known(0x07));

    /* Pages: CT32 64x32, CT16 64x64, T8 128x64, T4 128x128. */
    check_page(GS_PSMCT32, 64, 32);
    check_page(GS_PSMCT16, 64, 64);
    check_page(GS_PSMCT16S, 64, 64);
    check_page(GS_PSMZ32, 64, 32);
    check_page(GS_PSMT8, 128, 64);
    check_page(GS_PSMT4, 128, 128);

    /* CT32 column layout: pixels 0-1 share the first 8 bytes with pixels 8-9 of the row below... */
    CHECK_EQ(gs_vram_offset(0, 1, GS_PSMCT32, 1, 0, NULL), 4u);
    CHECK_EQ(gs_vram_offset(0, 1, GS_PSMCT32, 2, 0, NULL), 16u);
    /* ...and the block to the right of block 0 is block 1. */
    CHECK_EQ(gs_vram_offset(0, 1, GS_PSMCT32, 8, 0, NULL), 256u);
    /* The next page row starts FBW pages on. */
    CHECK_EQ(gs_vram_offset(0, 2, GS_PSMCT32, 0, 32, NULL), 2u * 8192u);
    CHECK_EQ(gs_vram_offset(0x20, 1, GS_PSMCT32, 0, 0, NULL), 8192u);
    /* Z32 flips the top block bits: Z pixel (0,0) is in block 24. */
    CHECK_EQ(gs_vram_offset(0, 1, GS_PSMZ32, 0, 0, NULL), 24u * 256u);

    unsigned psms[] = { GS_PSMCT32, GS_PSMCT24, GS_PSMCT16, GS_PSMCT16S, GS_PSMT8, GS_PSMT4, GS_PSMT8H, GS_PSMT4HL,
        GS_PSMT4HH, GS_PSMZ32, GS_PSMZ24, GS_PSMZ16, GS_PSMZ16S };
    for (size_t i = 0; i < sizeof(psms) / sizeof(psms[0]); i++)
        check_roundtrip(vram, psms[i]);

    /* Writes leave the bits of a word they don't own alone. */
    memset(vram, 0, GS_VRAM_SIZE);
    gs_vram_write(vram, 0, 1, GS_PSMCT32, 3, 3, 0xAABBCCDDu);
    gs_vram_write(vram, 0, 1, GS_PSMCT24, 3, 3, 0x112233u);
    CHECK_EQ(gs_vram_read(vram, 0, 1, GS_PSMCT32, 3, 3), 0xAA112233u);
    gs_vram_write(vram, 0, 1, GS_PSMT8H, 3, 3, 0x44);
    CHECK_EQ(gs_vram_read(vram, 0, 1, GS_PSMCT32, 3, 3), 0x44112233u);
    gs_vram_write(vram, 0, 1, GS_PSMT4HL, 3, 3, 0x5);
    gs_vram_write(vram, 0, 1, GS_PSMT4HH, 3, 3, 0x6);
    CHECK_EQ(gs_vram_read(vram, 0, 1, GS_PSMCT32, 3, 3), 0x65112233u);

    /* Colour conversion. */
    uint64_t texa = 0x40 | 1ull << 15 | 0x7Full << 32; /* TA0 0x40, AEM, TA1 0x7F */
    CHECK_EQ(gs_color_to_rgba(GS_PSMCT16, 0x801F, texa), 0x7F0000F8u);
    CHECK_EQ(gs_color_to_rgba(GS_PSMCT16, 0x03E0, texa), 0x4000F800u);
    CHECK_EQ(gs_color_to_rgba(GS_PSMCT16, 0x0000, texa), 0x00000000u);
    CHECK_EQ(gs_color_to_rgba(GS_PSMCT24, 0x123456, texa), 0x40123456u);
    CHECK_EQ(gs_color_to_rgba(GS_PSMCT24, 0, texa), 0u);
    CHECK_EQ(gs_color_to_rgba(GS_PSMCT32, 0x80FFFFFFu, texa), 0x80FFFFFFu);

    int w, h;
    gs_tex_size(3ull << 26 | 5ull << 30, &w, &h);
    CHECK_EQ(w, 8);
    CHECK_EQ(h, 32);

    /* CT32 texture decode. */
    memset(vram, 0, GS_VRAM_SIZE);
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            gs_vram_write(vram, 0x100, 1, GS_PSMCT32, x, y, 0x80000000u | (uint32_t)(y * 4 + x));
    struct gs_tex_regs regs = { 0x100 | 1ull << 14 | 2ull << 26 | 2ull << 30, 0, 0 };
    uint8_t rgba[256 * 4];
    CHECK_EQ(gs_decode_texture(vram, &regs, rgba), 0);
    CHECK_EQ(rgba[(2 * 4 + 3) * 4], 11);
    CHECK_EQ(rgba[(2 * 4 + 3) * 4 + 3], 0x80);

    /*
     * T8 with a CSM1 CT32 CLUT at CBP 0x200: entry i sits in a 16x16 image at
     * position i with bits 3 and 4 swapped, so entry 8 is at (0, 1) and
     * entry 16 at (8, 0).
     */
    memset(vram, 0, GS_VRAM_SIZE);
    for (unsigned i = 0; i < 256; i++) {
        unsigned p = (i & 0xE7) | ((i & 0x08) << 1) | ((i & 0x10) >> 1);
        gs_vram_write(vram, 0x200, 1, GS_PSMCT32, (int)(p & 15), (int)(p >> 4), 0x80000000u | i << 8 | i);
    }
    CHECK_EQ(gs_vram_read(vram, 0x200, 1, GS_PSMCT32, 0, 1), 0x80000808u);
    CHECK_EQ(gs_vram_read(vram, 0x200, 1, GS_PSMCT32, 8, 0), 0x80001010u);
    for (int y = 0; y < 16; y++)
        for (int x = 0; x < 16; x++)
            gs_vram_write(vram, 0x100, 2, GS_PSMT8, x, y, (uint32_t)(y * 16 + x));
    regs.tex0 = 0x100 | 2ull << 14 | (uint64_t)GS_PSMT8 << 20 | 4ull << 26 | 4ull << 30 | 0x200ull << 37;
    CHECK_EQ(gs_decode_texture(vram, &regs, rgba), 0);
    int clut_ok = 1;
    for (unsigned i = 0; i < 256; i++)
        if (rgba[i * 4] != i || rgba[i * 4 + 1] != i || rgba[i * 4 + 3] != 0x80)
            clut_ok = 0;
    CHECK(clut_ok);

    /* T4 with a CSM1 CT16 CLUT: 8x2 entries, no swizzle. */
    memset(vram, 0, GS_VRAM_SIZE);
    for (unsigned i = 0; i < 16; i++)
        gs_vram_write(vram, 0x300, 1, GS_PSMCT16, (int)(i & 7), (int)(i >> 3), 0x8000 | i);
    for (int x = 0; x < 16; x++)
        gs_vram_write(vram, 0x100, 2, GS_PSMT4, x, 0, (uint32_t)(15 - x));
    regs.tex0 = 0x100 | 2ull << 14 | (uint64_t)GS_PSMT4 << 20 | 4ull << 26 | 0ull << 30 | 0x300ull << 37 |
        (uint64_t)GS_PSMCT16 << 51;
    regs.texa = 0x7Full << 32;
    CHECK_EQ(gs_decode_texture(vram, &regs, rgba), 0);
    CHECK_EQ(rgba[0], (15 & 31) << 3);
    CHECK_EQ(rgba[3], 0x7F);
    CHECK_EQ(rgba[15 * 4], 0);

    /* Unknown modes decode to transparent black and fail. */
    regs.tex0 = 0x07ull << 20;
    CHECK_EQ(gs_decode_texture(vram, &regs, rgba), -1);

    free(vram);
    return check_finish("test_gs_vram");
}
