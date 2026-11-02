/*
 * GS local memory (4 MiB VRAM): swizzled addressing for every pixel storage
 * mode, single-pixel reads and writes, and texture decoding to RGBA8.
 *
 * Addresses follow the GS User's Manual: memory is split into 8 KiB pages and
 * 256-byte blocks, and each storage mode lays its pixels out across them in its
 * own order. `bp` is a block pointer (256-byte units) and `bw` a buffer width
 * in 64-pixel units, as in the FRAME, TEX0 and BITBLTBUF registers.
 */
#ifndef SOTC_PORT_RENDER_GS_VRAM_H
#define SOTC_PORT_RENDER_GS_VRAM_H

#include <stddef.h>
#include <stdint.h>

#define GS_VRAM_SIZE (4u * 1024u * 1024u)

/* Bits per pixel of a storage mode (32, 24, 16, 8 or 4), or 0 if unknown. */
unsigned gs_psm_bpp(unsigned psm);

/* Whether gs_vram_read/gs_vram_write handle this storage mode. */
int gs_psm_known(unsigned psm);

/*
 * Reads one pixel. CT24/Z24 return the low 24 bits, CT16 and Z16 the low 16,
 * T8/T8H 8 bits and T4/T4HL/T4HH 4 bits.
 */
uint32_t gs_vram_read(const uint8_t *vram, uint32_t bp, uint32_t bw, unsigned psm, int x, int y);

/* Writes one pixel, leaving the bits of the word this mode doesn't own alone. */
void gs_vram_write(uint8_t *vram, uint32_t bp, uint32_t bw, unsigned psm, int x, int y, uint32_t value);

/*
 * Byte offset into VRAM of the pixel's storage unit, for tests and for checking
 * which blocks a transfer touches. For 4-bit modes it is the byte that holds
 * the nibble; *nibble (if not NULL) says which half (0 low, 1 high).
 */
uint32_t gs_vram_offset(uint32_t bp, uint32_t bw, unsigned psm, int x, int y, unsigned *nibble);

/* Texture-relevant register values for decoding (raw 64-bit GS registers). */
struct gs_tex_regs {
    uint64_t tex0;
    uint64_t texa;
    uint64_t texclut;
};

/* Texture size from TEX0 (1 << TW by 1 << TH, each at most 1024). */
void gs_tex_size(uint64_t tex0, int *width, int *height);

/*
 * Decodes the texture described by TEX0 to RGBA8 (width * height * 4 bytes,
 * size from gs_tex_size). Alpha stays in GS units, where 0x80 means 1.0.
 * Indexed modes read their CLUT from VRAM at CBP (CSM1 swizzle or CSM2 with
 * TEXCLUT), not from a CLUT buffer loaded earlier: see docs/render-translator.md.
 * Returns 0 on success, -1 for a storage mode it doesn't support.
 */
int gs_decode_texture(const uint8_t *vram, const struct gs_tex_regs *regs, uint8_t *rgba);

/* Converts one stored colour of a colour mode (CT32/24/16/16S) to RGBA8 using TEXA. */
uint32_t gs_color_to_rgba(unsigned psm, uint32_t value, uint64_t texa);

#endif
