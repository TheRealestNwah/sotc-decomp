/*
 * GS register addresses, pixel storage modes and bitfield helpers.
 *
 * Field layouts follow the GS User's Manual. Registers are kept as raw 64-bit
 * values and read through the GS_FIELD helper, so a dump's register state can
 * be copied in unchanged.
 */
#ifndef SOTC_PORT_RENDER_GS_REGS_H
#define SOTC_PORT_RENDER_GS_REGS_H

#include <stdint.h>

/* Extracts `width` bits of `value` starting at bit `lo`. */
#define GS_FIELD(value, lo, width) ((uint32_t)(((uint64_t)(value) >> (lo)) & ((1ull << (width)) - 1)))

/* General-purpose GS registers, as A+D addresses. */
enum {
    GS_PRIM = 0x00,
    GS_RGBAQ = 0x01,
    GS_ST = 0x02,
    GS_UV = 0x03,
    GS_XYZF2 = 0x04,
    GS_XYZ2 = 0x05,
    GS_TEX0_1 = 0x06,
    GS_TEX0_2 = 0x07,
    GS_CLAMP_1 = 0x08,
    GS_CLAMP_2 = 0x09,
    GS_FOG = 0x0A,
    GS_XYZF3 = 0x0C,
    GS_XYZ3 = 0x0D,
    GS_TEX1_1 = 0x14,
    GS_TEX1_2 = 0x15,
    GS_TEX2_1 = 0x16,
    GS_TEX2_2 = 0x17,
    GS_XYOFFSET_1 = 0x18,
    GS_XYOFFSET_2 = 0x19,
    GS_PRMODECONT = 0x1A,
    GS_PRMODE = 0x1B,
    GS_TEXCLUT = 0x1C,
    GS_SCANMSK = 0x22,
    GS_MIPTBP1_1 = 0x34,
    GS_MIPTBP1_2 = 0x35,
    GS_MIPTBP2_1 = 0x36,
    GS_MIPTBP2_2 = 0x37,
    GS_TEXA = 0x3B,
    GS_FOGCOL = 0x3D,
    GS_TEXFLUSH = 0x3F,
    GS_SCISSOR_1 = 0x40,
    GS_SCISSOR_2 = 0x41,
    GS_ALPHA_1 = 0x42,
    GS_ALPHA_2 = 0x43,
    GS_DIMX = 0x44,
    GS_DTHE = 0x45,
    GS_COLCLAMP = 0x46,
    GS_TEST_1 = 0x47,
    GS_TEST_2 = 0x48,
    GS_PABE = 0x49,
    GS_FBA_1 = 0x4A,
    GS_FBA_2 = 0x4B,
    GS_FRAME_1 = 0x4C,
    GS_FRAME_2 = 0x4D,
    GS_ZBUF_1 = 0x4E,
    GS_ZBUF_2 = 0x4F,
    GS_BITBLTBUF = 0x50,
    GS_TRXPOS = 0x51,
    GS_TRXREG = 0x52,
    GS_TRXDIR = 0x53,
    GS_HWREG = 0x54,
    GS_SIGNAL = 0x60,
    GS_FINISH = 0x61,
    GS_LABEL = 0x62,
    GS_REG_COUNT = 0x63
};

/* Pixel storage modes (PSM fields). */
enum {
    GS_PSMCT32 = 0x00,
    GS_PSMCT24 = 0x01,
    GS_PSMCT16 = 0x02,
    GS_PSMCT16S = 0x0A,
    GS_PSMT8 = 0x13,
    GS_PSMT4 = 0x14,
    GS_PSMT8H = 0x1B,
    GS_PSMT4HL = 0x24,
    GS_PSMT4HH = 0x2C,
    GS_PSMZ32 = 0x30,
    GS_PSMZ24 = 0x31,
    GS_PSMZ16 = 0x32,
    GS_PSMZ16S = 0x3A
};

/* PRIM.PRIM primitive types. */
enum {
    GS_PRIM_POINT = 0,
    GS_PRIM_LINE = 1,
    GS_PRIM_LINESTRIP = 2,
    GS_PRIM_TRIANGLE = 3,
    GS_PRIM_TRISTRIP = 4,
    GS_PRIM_TRIFAN = 5,
    GS_PRIM_SPRITE = 6,
    GS_PRIM_INVALID = 7
};

/* Privileged registers, as byte offsets into a dump's 0x2000-byte register block. */
enum {
    GS_PRIV_PMODE = 0x0000,
    GS_PRIV_SMODE1 = 0x0010,
    GS_PRIV_SMODE2 = 0x0020,
    GS_PRIV_DISPFB1 = 0x0070,
    GS_PRIV_DISPLAY1 = 0x0080,
    GS_PRIV_DISPFB2 = 0x0090,
    GS_PRIV_DISPLAY2 = 0x00A0,
    GS_PRIV_BGCOLOR = 0x00E0,
    GS_PRIV_CSR = 0x1000,
    GS_PRIV_IMR = 0x1010,
    GS_PRIV_SIZE = 0x2000
};

#endif
