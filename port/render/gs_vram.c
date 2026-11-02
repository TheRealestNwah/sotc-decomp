#include "gs_vram.h"

#include "gs_regs.h"

#include <string.h>

/* Block order inside a page, by block row and column. */
static const uint8_t block32[4][8] = {
    { 0, 1, 4, 5, 16, 17, 20, 21 },
    { 2, 3, 6, 7, 18, 19, 22, 23 },
    { 8, 9, 12, 13, 24, 25, 28, 29 },
    { 10, 11, 14, 15, 26, 27, 30, 31 },
};

static const uint8_t block16[8][4] = {
    { 0, 2, 8, 10 },
    { 1, 3, 9, 11 },
    { 4, 6, 12, 14 },
    { 5, 7, 13, 15 },
    { 16, 18, 24, 26 },
    { 17, 19, 25, 27 },
    { 20, 22, 28, 30 },
    { 21, 23, 29, 31 },
};

static const uint8_t block16s[8][4] = {
    { 0, 2, 16, 18 },
    { 1, 3, 17, 19 },
    { 8, 10, 24, 26 },
    { 9, 11, 25, 27 },
    { 4, 6, 20, 22 },
    { 5, 7, 21, 23 },
    { 12, 14, 28, 30 },
    { 13, 15, 29, 31 },
};

/* PSMT8 uses the PSMCT32 block order; PSMT4 uses the PSMCT16 one. */

/* Word inside a block, by pixel row and column (PSMCT32). */
static const uint8_t column32[8][8] = {
    { 0, 1, 4, 5, 8, 9, 12, 13 },
    { 2, 3, 6, 7, 10, 11, 14, 15 },
    { 16, 17, 20, 21, 24, 25, 28, 29 },
    { 18, 19, 22, 23, 26, 27, 30, 31 },
    { 32, 33, 36, 37, 40, 41, 44, 45 },
    { 34, 35, 38, 39, 42, 43, 46, 47 },
    { 48, 49, 52, 53, 56, 57, 60, 61 },
    { 50, 51, 54, 55, 58, 59, 62, 63 },
};

/* Halfword inside a block (PSMCT16). */
static const uint8_t column16[8][16] = {
    { 0, 2, 8, 10, 16, 18, 24, 26, 1, 3, 9, 11, 17, 19, 25, 27 },
    { 4, 6, 12, 14, 20, 22, 28, 30, 5, 7, 13, 15, 21, 23, 29, 31 },
    { 32, 34, 40, 42, 48, 50, 56, 58, 33, 35, 41, 43, 49, 51, 57, 59 },
    { 36, 38, 44, 46, 52, 54, 60, 62, 37, 39, 45, 47, 53, 55, 61, 63 },
    { 64, 66, 72, 74, 80, 82, 88, 90, 65, 67, 73, 75, 81, 83, 89, 91 },
    { 68, 70, 76, 78, 84, 86, 92, 94, 69, 71, 77, 79, 85, 87, 93, 95 },
    { 96, 98, 104, 106, 112, 114, 120, 122, 97, 99, 105, 107, 113, 115, 121, 123 },
    { 100, 102, 108, 110, 116, 118, 124, 126, 101, 103, 109, 111, 117, 119, 125, 127 },
};

/* Byte inside a block (PSMT8). */
static const uint8_t column8[16][16] = {
    { 0, 4, 16, 20, 32, 36, 48, 52, 2, 6, 18, 22, 34, 38, 50, 54 },
    { 8, 12, 24, 28, 40, 44, 56, 60, 10, 14, 26, 30, 42, 46, 58, 62 },
    { 33, 37, 49, 53, 1, 5, 17, 21, 35, 39, 51, 55, 3, 7, 19, 23 },
    { 41, 45, 57, 61, 9, 13, 25, 29, 43, 47, 59, 63, 11, 15, 27, 31 },
    { 96, 100, 112, 116, 64, 68, 80, 84, 98, 102, 114, 118, 66, 70, 82, 86 },
    { 104, 108, 120, 124, 72, 76, 88, 92, 106, 110, 122, 126, 74, 78, 90, 94 },
    { 65, 69, 81, 85, 97, 101, 113, 117, 67, 71, 83, 87, 99, 103, 115, 119 },
    { 73, 77, 89, 93, 105, 109, 121, 125, 75, 79, 91, 95, 107, 111, 123, 127 },
    { 128, 132, 144, 148, 160, 164, 176, 180, 130, 134, 146, 150, 162, 166, 178, 182 },
    { 136, 140, 152, 156, 168, 172, 184, 188, 138, 142, 154, 158, 170, 174, 186, 190 },
    { 161, 165, 177, 181, 129, 133, 145, 149, 163, 167, 179, 183, 131, 135, 147, 151 },
    { 169, 173, 185, 189, 137, 141, 153, 157, 171, 175, 187, 191, 139, 143, 155, 159 },
    { 224, 228, 240, 244, 192, 196, 208, 212, 226, 230, 242, 246, 194, 198, 210, 214 },
    { 232, 236, 248, 252, 200, 204, 216, 220, 234, 238, 250, 254, 202, 206, 218, 222 },
    { 193, 197, 209, 213, 225, 229, 241, 245, 195, 199, 211, 215, 227, 231, 243, 247 },
    { 201, 205, 217, 221, 233, 237, 249, 253, 203, 207, 219, 223, 235, 239, 251, 255 },
};

/* Nibble inside a block (PSMT4). */
static const uint16_t column4[16][32] = {
    { 0, 8, 32, 40, 64, 72, 96, 104, 2, 10, 34, 42, 66, 74, 98, 106,
      4, 12, 36, 44, 68, 76, 100, 108, 6, 14, 38, 46, 70, 78, 102, 110 },
    { 16, 24, 48, 56, 80, 88, 112, 120, 18, 26, 50, 58, 82, 90, 114, 122,
      20, 28, 52, 60, 84, 92, 116, 124, 22, 30, 54, 62, 86, 94, 118, 126 },
    { 65, 73, 97, 105, 1, 9, 33, 41, 67, 75, 99, 107, 3, 11, 35, 43,
      69, 77, 101, 109, 5, 13, 37, 45, 71, 79, 103, 111, 7, 15, 39, 47 },
    { 81, 89, 113, 121, 17, 25, 49, 57, 83, 91, 115, 123, 19, 27, 51, 59,
      85, 93, 117, 125, 21, 29, 53, 61, 87, 95, 119, 127, 23, 31, 55, 63 },
    { 192, 200, 224, 232, 128, 136, 160, 168, 194, 202, 226, 234, 130, 138, 162, 170,
      196, 204, 228, 236, 132, 140, 164, 172, 198, 206, 230, 238, 134, 142, 166, 174 },
    { 208, 216, 240, 248, 144, 152, 176, 184, 210, 218, 242, 250, 146, 154, 178, 186,
      212, 220, 244, 252, 148, 156, 180, 188, 214, 222, 246, 254, 150, 158, 182, 190 },
    { 129, 137, 161, 169, 193, 201, 225, 233, 131, 139, 163, 171, 195, 203, 227, 235,
      133, 141, 165, 173, 197, 205, 229, 237, 135, 143, 167, 175, 199, 207, 231, 239 },
    { 145, 153, 177, 185, 209, 217, 241, 249, 147, 155, 179, 187, 211, 219, 243, 251,
      149, 157, 181, 189, 213, 221, 245, 253, 151, 159, 183, 191, 215, 223, 247, 255 },
    { 256, 264, 288, 296, 320, 328, 352, 360, 258, 266, 290, 298, 322, 330, 354, 362,
      260, 268, 292, 300, 324, 332, 356, 364, 262, 270, 294, 302, 326, 334, 358, 366 },
    { 272, 280, 304, 312, 336, 344, 368, 376, 274, 282, 306, 314, 338, 346, 370, 378,
      276, 284, 308, 316, 340, 348, 372, 380, 278, 286, 310, 318, 342, 350, 374, 382 },
    { 321, 329, 353, 361, 257, 265, 289, 297, 323, 331, 355, 363, 259, 267, 291, 299,
      325, 333, 357, 365, 261, 269, 293, 301, 327, 335, 359, 367, 263, 271, 295, 303 },
    { 337, 345, 369, 377, 273, 281, 305, 313, 339, 347, 371, 379, 275, 283, 307, 315,
      341, 349, 373, 381, 277, 285, 309, 317, 343, 351, 375, 383, 279, 287, 311, 319 },
    { 448, 456, 480, 488, 384, 392, 416, 424, 450, 458, 482, 490, 386, 394, 418, 426,
      452, 460, 484, 492, 388, 396, 420, 428, 454, 462, 486, 494, 390, 398, 422, 430 },
    { 464, 472, 496, 504, 400, 408, 432, 440, 466, 474, 498, 506, 402, 410, 434, 442,
      468, 476, 500, 508, 404, 412, 436, 444, 470, 478, 502, 510, 406, 414, 438, 446 },
    { 385, 393, 417, 425, 449, 457, 481, 489, 387, 395, 419, 427, 451, 459, 483, 491,
      389, 397, 421, 429, 453, 461, 485, 493, 391, 399, 423, 431, 455, 463, 487, 495 },
    { 401, 409, 433, 441, 465, 473, 497, 505, 403, 411, 435, 443, 467, 475, 499, 507,
      405, 413, 437, 445, 469, 477, 501, 509, 407, 415, 439, 447, 471, 479, 503, 511 },
};

unsigned gs_psm_bpp(unsigned psm)
{
    switch (psm) {
    case GS_PSMCT32:
    case GS_PSMZ32:
        return 32;
    case GS_PSMCT24:
    case GS_PSMZ24:
        return 24;
    case GS_PSMCT16:
    case GS_PSMCT16S:
    case GS_PSMZ16:
    case GS_PSMZ16S:
        return 16;
    case GS_PSMT8:
    case GS_PSMT8H:
        return 8;
    case GS_PSMT4:
    case GS_PSMT4HL:
    case GS_PSMT4HH:
        return 4;
    default:
        return 0;
    }
}

int gs_psm_known(unsigned psm)
{
    return gs_psm_bpp(psm) != 0;
}

/* Z buffers use the colour layouts with the block number's top two bits flipped. */
static int psm_is_z(unsigned psm)
{
    return (psm & 0x30) == 0x30;
}

/* Byte offset of a 32-bit word (CT32/CT24/Z32/Z24 and the H modes). */
static uint32_t offset32(uint32_t bp, uint32_t bw, int x, int y, int z)
{
    uint32_t page = (uint32_t)(y >> 5) * bw + (uint32_t)(x >> 6);
    uint32_t block = block32[(y >> 3) & 3][(x >> 3) & 7];
    if (z)
        block ^= 24;
    uint32_t blk = (bp + page * 32 + block) & 0x3FFF;
    return blk * 256 + column32[y & 7][x & 7] * 4u;
}

static uint32_t offset16(uint32_t bp, uint32_t bw, int x, int y, int s, int z)
{
    uint32_t page = (uint32_t)(y >> 6) * bw + (uint32_t)(x >> 6);
    uint32_t block = s ? block16s[(y >> 3) & 7][(x >> 4) & 3] : block16[(y >> 3) & 7][(x >> 4) & 3];
    if (z)
        block ^= 24;
    uint32_t blk = (bp + page * 32 + block) & 0x3FFF;
    return blk * 256 + column16[y & 7][x & 15] * 2u;
}

static uint32_t offset8(uint32_t bp, uint32_t bw, int x, int y)
{
    uint32_t page = (uint32_t)(y >> 6) * (bw >> 1) + (uint32_t)(x >> 7);
    uint32_t blk = (bp + page * 32 + block32[(y >> 4) & 3][(x >> 4) & 7]) & 0x3FFF;
    return blk * 256 + column8[y & 15][x & 15];
}

static uint32_t offset4(uint32_t bp, uint32_t bw, int x, int y, unsigned *nibble)
{
    uint32_t page = (uint32_t)(y >> 7) * (bw >> 1) + (uint32_t)(x >> 7);
    uint32_t blk = (bp + page * 32 + block16[(y >> 4) & 7][(x >> 5) & 3]) & 0x3FFF;
    uint32_t n = blk * 512 + column4[y & 15][x & 31];
    if (nibble)
        *nibble = n & 1;
    return n >> 1;
}

uint32_t gs_vram_offset(uint32_t bp, uint32_t bw, unsigned psm, int x, int y, unsigned *nibble)
{
    if (nibble)
        *nibble = 0;
    x &= 2047;
    y &= 2047;
    /* The H modes keep their texels in the top bits of a CT32 layout. */
    if (psm == GS_PSMT8H || psm == GS_PSMT4HL || psm == GS_PSMT4HH)
        return offset32(bp, bw, x, y, 0);
    switch (gs_psm_bpp(psm)) {
    case 32:
    case 24:
        return offset32(bp, bw, x, y, psm_is_z(psm));
    case 16:
        return offset16(bp, bw, x, y, psm == GS_PSMCT16S || psm == GS_PSMZ16S, psm_is_z(psm));
    case 8:
        return offset8(bp, bw, x, y);
    case 4:
        return offset4(bp, bw, x, y, nibble);
    default:
        return 0;
    }
}

static uint32_t load32(const uint8_t *p)
{
    return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}

static void store32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

uint32_t gs_vram_read(const uint8_t *vram, uint32_t bp, uint32_t bw, unsigned psm, int x, int y)
{
    unsigned nib;
    uint32_t off = gs_vram_offset(bp, bw, psm, x, y, &nib);
    switch (psm) {
    case GS_PSMCT32:
    case GS_PSMZ32:
        return load32(vram + off);
    case GS_PSMCT24:
    case GS_PSMZ24:
        return load32(vram + off) & 0xFFFFFF;
    case GS_PSMCT16:
    case GS_PSMCT16S:
    case GS_PSMZ16:
    case GS_PSMZ16S:
        return (uint32_t)vram[off] | (uint32_t)vram[off + 1] << 8;
    case GS_PSMT8:
        return vram[off];
    case GS_PSMT4:
        return (vram[off] >> (nib * 4)) & 0xF;
    case GS_PSMT8H:
        return vram[off + 3];
    case GS_PSMT4HL:
        return vram[off + 3] & 0xF;
    case GS_PSMT4HH:
        return vram[off + 3] >> 4;
    default:
        return 0;
    }
}

void gs_vram_write(uint8_t *vram, uint32_t bp, uint32_t bw, unsigned psm, int x, int y, uint32_t value)
{
    unsigned nib;
    uint32_t off = gs_vram_offset(bp, bw, psm, x, y, &nib);
    switch (psm) {
    case GS_PSMCT32:
    case GS_PSMZ32:
        store32(vram + off, value);
        break;
    case GS_PSMCT24:
    case GS_PSMZ24:
        vram[off] = (uint8_t)value;
        vram[off + 1] = (uint8_t)(value >> 8);
        vram[off + 2] = (uint8_t)(value >> 16);
        break;
    case GS_PSMCT16:
    case GS_PSMCT16S:
    case GS_PSMZ16:
    case GS_PSMZ16S:
        vram[off] = (uint8_t)value;
        vram[off + 1] = (uint8_t)(value >> 8);
        break;
    case GS_PSMT8:
        vram[off] = (uint8_t)value;
        break;
    case GS_PSMT4:
        vram[off] = (uint8_t)(nib ? (vram[off] & 0x0F) | (value & 0xF) << 4 : (vram[off] & 0xF0) | (value & 0xF));
        break;
    case GS_PSMT8H:
        vram[off + 3] = (uint8_t)value;
        break;
    case GS_PSMT4HL:
        vram[off + 3] = (uint8_t)((vram[off + 3] & 0xF0) | (value & 0xF));
        break;
    case GS_PSMT4HH:
        vram[off + 3] = (uint8_t)((vram[off + 3] & 0x0F) | (value & 0xF) << 4);
        break;
    default:
        break;
    }
}

void gs_tex_size(uint64_t tex0, int *width, int *height)
{
    unsigned tw = GS_FIELD(tex0, 26, 4), th = GS_FIELD(tex0, 30, 4);
    *width = 1 << (tw > 10 ? 10 : tw);
    *height = 1 << (th > 10 ? 10 : th);
}

uint32_t gs_color_to_rgba(unsigned psm, uint32_t value, uint64_t texa)
{
    uint32_t ta0 = GS_FIELD(texa, 0, 8), ta1 = GS_FIELD(texa, 32, 8);
    int aem = (int)GS_FIELD(texa, 15, 1);
    switch (psm) {
    case GS_PSMCT32:
        return value;
    case GS_PSMCT24: {
        uint32_t rgb = value & 0xFFFFFF;
        uint32_t a = (aem && rgb == 0) ? 0 : ta0;
        return rgb | a << 24;
    }
    case GS_PSMCT16:
    case GS_PSMCT16S: {
        uint32_t r = (value & 31) << 3, g = ((value >> 5) & 31) << 3, b = ((value >> 10) & 31) << 3;
        uint32_t a;
        if (value & 0x8000)
            a = ta1;
        else
            a = (aem && (value & 0x7FFF) == 0) ? 0 : ta0;
        return r | g << 8 | b << 16 | a << 24;
    }
    default:
        return 0;
    }
}

/* Reads CLUT entry `index` for an indexed texture. */
static uint32_t clut_entry(const uint8_t *vram, const struct gs_tex_regs *regs, unsigned index, int eight_bit)
{
    uint32_t cbp = GS_FIELD(regs->tex0, 37, 14);
    unsigned cpsm = GS_FIELD(regs->tex0, 51, 4);
    unsigned csm = GS_FIELD(regs->tex0, 55, 1);
    unsigned cmode = (cpsm == 0) ? GS_PSMCT32 : (cpsm == 0xA ? GS_PSMCT16S : GS_PSMCT16);
    int x, y;
    uint32_t bw = 1;

    if (csm == 0) {
        if (eight_bit) {
            /* CSM1 stores 256 entries as a 16x16 image with index bits 3 and 4 swapped. */
            unsigned p = (index & 0xE7) | ((index & 0x08) << 1) | ((index & 0x10) >> 1);
            x = (int)(p & 15);
            y = (int)(p >> 4);
        } else {
            x = (int)(index & 7);
            y = (int)(index >> 3);
        }
    } else {
        /* CSM2: a linear row at (COU * 16, COV) in a CBW-wide buffer, CT16 only. */
        bw = GS_FIELD(regs->texclut, 0, 6);
        x = (int)(GS_FIELD(regs->texclut, 6, 6) * 16 + index);
        y = (int)GS_FIELD(regs->texclut, 12, 10);
        cmode = GS_PSMCT16;
    }
    return gs_color_to_rgba(cmode, gs_vram_read(vram, cbp, bw, cmode, x, y), regs->texa);
}

int gs_decode_texture(const uint8_t *vram, const struct gs_tex_regs *regs, uint8_t *rgba)
{
    uint32_t tbp = GS_FIELD(regs->tex0, 0, 14);
    uint32_t tbw = GS_FIELD(regs->tex0, 14, 6);
    unsigned psm = GS_FIELD(regs->tex0, 20, 6);
    int w, h;
    gs_tex_size(regs->tex0, &w, &h);

    uint32_t clut[256];
    int indexed = 0;
    switch (psm) {
    case GS_PSMCT32:
    case GS_PSMCT24:
    case GS_PSMCT16:
    case GS_PSMCT16S:
        break;
    case GS_PSMT8:
    case GS_PSMT8H:
        for (unsigned i = 0; i < 256; i++)
            clut[i] = clut_entry(vram, regs, i, 1);
        indexed = 1;
        break;
    case GS_PSMT4:
    case GS_PSMT4HL:
    case GS_PSMT4HH:
        for (unsigned i = 0; i < 16; i++)
            clut[i] = clut_entry(vram, regs, i, 0);
        indexed = 1;
        break;
    default:
        memset(rgba, 0, (size_t)w * (size_t)h * 4);
        return -1;
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            uint32_t v = gs_vram_read(vram, tbp, tbw, psm, x, y);
            uint32_t c = indexed ? clut[v] : gs_color_to_rgba(psm, v, regs->texa);
            store32(rgba + ((size_t)y * (size_t)w + (size_t)x) * 4, c);
        }
    }
    return 0;
}
