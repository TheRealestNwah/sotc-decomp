/* Reference backend: draws translated batches into a 64x64 target (synthetic data only). */
#include "check.h"
#include "gif.h"
#include "gs_ref.h"
#include "gs_regs.h"
#include "gs_translate.h"
#include "gs_vram.h"

#include <stdlib.h>
#include <string.h>

static struct gs_translator t;
static struct gs_ref ref;
static int live;

/* Frame at FBP 0, 64 pixels wide, CT32; scissor 64x64; no tests. */
static void start(void)
{
    if (live) {
        gs_ref_free(&ref);
        gs_translator_free(&t);
    }
    if (gs_translator_init(&t, NULL) != 0)
        exit(1);
    gs_ref_init(&ref, t.vram);
    t.sink = gs_ref_sink(&ref);
    live = 1;
    gs_translator_write(&t, GS_FRAME_1, gs_frame(0, 1, GS_PSMCT32, 0));
    gs_translator_write(&t, GS_SCISSOR_1, gs_scissor(0, 63, 0, 63));
    gs_translator_write(&t, GS_TEST_1, 0);
    gs_translator_write(&t, GS_COLCLAMP, 1);
}

static void colour(unsigned r, unsigned g, unsigned b, unsigned a)
{
    gs_translator_write(&t, GS_RGBAQ, (uint64_t)r | (uint64_t)g << 8 | (uint64_t)b << 16 | (uint64_t)a << 24 | 0x3F800000ull << 32);
}

static void vertex(unsigned x, unsigned y, uint32_t z)
{
    gs_translator_write(&t, GS_XYZ2, (uint64_t)(x * 16) | (uint64_t)(y * 16) << 16 | (uint64_t)z << 32);
}

static void uv(unsigned u, unsigned v)
{
    gs_translator_write(&t, GS_UV, (uint64_t)(u * 16) | (uint64_t)(v * 16) << 16);
}

static void rect(uint64_t prim, unsigned x0, unsigned y0, unsigned x1, unsigned y1, uint32_t z, unsigned r, unsigned g,
    unsigned b, unsigned a)
{
    gs_translator_write(&t, GS_PRIM, prim);
    colour(r, g, b, a);
    vertex(x0, y0, z);
    vertex(x1, y1, z);
}

static uint32_t pixel(uint32_t fbp, int x, int y)
{
    gs_translator_flush(&t);
    const struct gs_ref_target *rt = gs_ref_find_target(&ref, fbp);
    uint32_t c = 0;
    if (rt)
        memcpy(&c, rt->rgba + ((size_t)y * rt->width + x) * 4, 4);
    return c;
}

/* Uploads a CT32 image through the GIF, as the game would. */
static void upload(unsigned dbp, unsigned dbw, unsigned w, unsigned h, const uint32_t *px)
{
    static struct gif g;
    g.size = 0;
    gif_tag(&g, 4, 0, 0, 0, 0, 1, 0xE);
    gif_ad(&g, GS_BITBLTBUF, gs_bitbltbuf(dbp, dbw, GS_PSMCT32));
    gif_ad(&g, GS_TRXPOS, gs_trxpos(0, 0, 0, 0));
    gif_ad(&g, GS_TRXREG, gs_trxreg(w, h));
    gif_ad(&g, GS_TRXDIR, 0);
    gif_tag(&g, w * h / 4, 1, 0, 0, 2, 0, 0);
    for (unsigned i = 0; i < w * h; i += 2)
        gif_u64(&g, (uint64_t)px[i] | (uint64_t)px[i + 1] << 32);
    gs_translator_gif(&t, 3, g.data, g.size);
}

static const uint64_t SPRITE = 6; /* PRIM: sprite, flat, untextured */

static void test_clear(void)
{
    start();
    rect(SPRITE, 0, 0, 64, 64, 0, 10, 20, 30, 0x80);
    CHECK_EQ(pixel(0, 0, 0), 0x801E140Au);
    CHECK_EQ(pixel(0, 63, 63), 0x801E140Au);
    CHECK_EQ(ref.stats.pixels, 4096u);
}

static void test_gouraud(void)
{
    start();
    /* Two triangles across the target, red 0 on the left and 255 on the right. */
    gs_translator_write(&t, GS_PRIM, gs_prim(GS_PRIM_TRISTRIP, 1, 0, 0, 0, 0, 0));
    colour(0, 0, 0, 0x80);
    vertex(0, 0, 0);
    vertex(0, 64, 0);
    colour(255, 0, 0, 0x80);
    vertex(64, 0, 0);
    vertex(64, 64, 0);
    int ok = 1, last = -1;
    for (int x = 0; x < 64; x++) {
        int r = (int)(pixel(0, x, 10) & 0xFF);
        if (r < last)
            ok = 0;
        last = r;
    }
    CHECK(ok);
    int mid = (int)(pixel(0, 32, 10) & 0xFF);
    CHECK(mid >= 124 && mid <= 132);
    CHECK((pixel(0, 0, 10) & 0xFF) <= 4);
}

static void test_textures(void)
{
    uint32_t tex[16], flat[16];
    for (unsigned i = 0; i < 16; i++) {
        tex[i] = 0x80000000u | (i * 10) << 16 | (i * 10);
        flat[i] = 0x40C8C8C8u; /* colour 200, alpha 0x40 */
    }

    /* DECAL: the sprite shows the texture, one texel per pixel. */
    start();
    upload(0x1000, 1, 4, 4, tex);
    gs_translator_write(&t, GS_TEX0_1, gs_tex0(0x1000, 1, GS_PSMCT32, 2, 2, 1, GS_TFX_DECAL, 0, 0));
    gs_translator_write(&t, GS_PRIM, gs_prim(GS_PRIM_SPRITE, 0, 1, 0, 0, 1, 0));
    colour(1, 2, 3, 0x80);
    uv(0, 0);
    vertex(0, 0, 0);
    uv(4, 4);
    vertex(4, 4, 0);
    int ok = 1;
    for (unsigned y = 0; y < 4; y++)
        for (unsigned x = 0; x < 4; x++)
            if (pixel(0, (int)x, (int)y) != tex[y * 4 + x])
                ok = 0;
    CHECK(ok);
    CHECK_EQ(ref.stats.bad_textures, 0u);

    /* MODULATE: 0x40 x 200 >> 7 is 100. */
    upload(0x1100, 1, 4, 4, flat);
    gs_translator_write(&t, GS_TEX0_1, gs_tex0(0x1100, 1, GS_PSMCT32, 2, 2, 1, GS_TFX_MODULATE, 0, 0));
    gs_translator_write(&t, GS_PRIM, gs_prim(GS_PRIM_SPRITE, 0, 1, 0, 0, 1, 0));
    colour(0x40, 0x40, 0x40, 0x80);
    uv(0, 0);
    vertex(8, 8, 0);
    uv(4, 4);
    vertex(12, 12, 0);
    CHECK_EQ(pixel(0, 9, 9), 0x40646464u); /* alpha 0x80 x 0x40 >> 7 */
}

static void test_blend(void)
{
    start();
    rect(SPRITE, 0, 0, 64, 64, 0, 60, 60, 60, 0x80);
    /* (Cs - Cd) * As + Cd: (100 - 60) * 0x40 / 128 + 60 = 80. */
    gs_translator_write(&t, GS_ALPHA_1, gs_alpha(0, 1, 0, 1, 0));
    rect(gs_prim(GS_PRIM_SPRITE, 0, 0, 0, 1, 0, 0), 0, 0, 8, 8, 0, 100, 100, 100, 0x40);
    CHECK_EQ(pixel(0, 4, 4) & 0xFFFFFF, 0x505050u);
    CHECK_EQ(pixel(0, 20, 4) & 0xFFFFFF, 0x3C3C3Cu);
}

static void test_depth(void)
{
    start();
    gs_translator_write(&t, GS_ZBUF_1, 4); /* ZBP 4, Z32, writes on */
    gs_translator_write(&t, GS_TEST_1, 1ull << 16 | 2ull << 17); /* ZTE, GEQUAL */
    rect(SPRITE, 0, 0, 8, 8, 100, 255, 0, 0, 0x80);
    rect(SPRITE, 0, 0, 8, 8, 50, 0, 255, 0, 0x80);
    CHECK_EQ(pixel(0, 2, 2), 0x800000FFu);
    rect(SPRITE, 0, 0, 8, 8, 200, 0, 0, 255, 0x80);
    CHECK_EQ(pixel(0, 2, 2), 0x80FF0000u);
}

static void set_display(uint32_t fbp, unsigned w, unsigned h)
{
    uint64_t pmode = 1, dispfb = (uint64_t)fbp | 1ull << 9, display = (uint64_t)(w - 1) << 32 | (uint64_t)(h - 1) << 44;
    memcpy(t.privregs + GS_PRIV_PMODE, &pmode, 8);
    memcpy(t.privregs + GS_PRIV_DISPFB1, &dispfb, 8);
    memcpy(t.privregs + GS_PRIV_DISPLAY1, &display, 8);
}

static void test_display(void)
{
    start();
    rect(SPRITE, 0, 0, 64, 64, 0, 10, 20, 30, 0x00);
    set_display(0, 64, 64);
    gs_translator_vsync(&t, 0);
    CHECK_EQ(ref.frame_width, 64);
    CHECK_EQ(ref.frame_height, 64);
    CHECK_EQ(ref.frames, 1u);
    uint32_t c;
    memcpy(&c, ref.frame + (63 * 64 + 63) * 4, 4);
    CHECK_EQ(c, 0xFF1E140Au);

    /* Nothing drawn at FBP 2: the frame comes from GS memory. */
    start();
    gs_vram_write(t.vram, 2 * 32, 1, GS_PSMCT32, 1, 1, 0x00112233u);
    set_display(2, 16, 8);
    gs_translator_vsync(&t, 0);
    CHECK_EQ(ref.frame_width, 16);
    CHECK_EQ(ref.frame_height, 8);
    memcpy(&c, ref.frame + (1 * 16 + 1) * 4, 4);
    CHECK_EQ(c, 0xFF112233u);
}

static void test_render_targets(void)
{
    start();
    rect(SPRITE, 0, 0, 64, 64, 0, 10, 20, 30, 0x80);
    /* Sample the target just drawn into a second one at FBP 16 (GS memory there is stale). */
    gs_translator_write(&t, GS_FRAME_1, gs_frame(16, 1, GS_PSMCT32, 0));
    gs_translator_write(&t, GS_TEX0_1, gs_tex0(0, 1, GS_PSMCT32, 6, 6, 1, GS_TFX_DECAL, 0, 0));
    gs_translator_write(&t, GS_PRIM, gs_prim(GS_PRIM_SPRITE, 0, 1, 0, 0, 1, 0));
    uv(0, 0);
    vertex(0, 0, 0);
    uv(8, 8);
    vertex(8, 8, 0);
    CHECK_EQ(pixel(16, 3, 3), 0x801E140Au);
    CHECK(ref.stats.rt_textures > 0);

    /* An upload over a target replaces what it shows there. */
    uint32_t px[4] = { 0x80010203u, 0x80010203u, 0x80010203u, 0x80010203u };
    upload(0, 1, 2, 2, px);
    CHECK_EQ(ref.stats.rt_refreshes, 1u);
    CHECK_EQ(pixel(0, 1, 1), 0x80010203u);
    CHECK_EQ(pixel(0, 2, 2), 0x801E140Au);
}

int main(void)
{
    test_clear();
    test_gouraud();
    test_textures();
    test_blend();
    test_depth();
    test_display();
    test_render_targets();
    gs_ref_free(&ref);
    gs_translator_free(&t);
    return check_finish("test_gs_ref");
}
