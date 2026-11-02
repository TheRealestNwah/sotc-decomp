/* Builds GIF packets by hand for the Render translator tests (synthetic data only). */
#ifndef SOTC_PORT_TESTS_GIF_H
#define SOTC_PORT_TESTS_GIF_H

#include <stddef.h>
#include <stdint.h>

#define GIF_MAX_QWORDS 4096

struct gif {
    uint8_t data[GIF_MAX_QWORDS * 16];
    size_t size;
};

static inline void gif_u64(struct gif *g, uint64_t v)
{
    for (int i = 0; i < 8; i++)
        g->data[g->size++] = (uint8_t)(v >> (8 * i));
}

static inline void gif_qword(struct gif *g, uint64_t lo, uint64_t hi)
{
    gif_u64(g, lo);
    gif_u64(g, hi);
}

/* A GIF tag. regs holds NREG 4-bit descriptors, the first in the low bits. */
static inline void gif_tag(struct gif *g, unsigned nloop, int eop, int pre, unsigned prim, unsigned flg, unsigned nreg,
    uint64_t regs)
{
    uint64_t lo = (uint64_t)nloop | (uint64_t)(eop & 1) << 15 | (uint64_t)(pre & 1) << 46 | (uint64_t)prim << 47 |
        (uint64_t)flg << 58 | (uint64_t)(nreg & 15) << 60;
    gif_qword(g, lo, regs);
}

/* One A+D qword: write `value` to register `reg`. */
static inline void gif_ad(struct gif *g, unsigned reg, uint64_t value)
{
    gif_qword(g, value, reg);
}

/* PACKED register data. */
static inline void gif_rgbaq(struct gif *g, unsigned r, unsigned gg, unsigned b, unsigned a)
{
    gif_qword(g, (uint64_t)r | (uint64_t)gg << 32, (uint64_t)b | (uint64_t)a << 32);
}

/* PACKED XYZ2 in 12.4 fixed point; adc 1 makes it XYZ3 (no drawing kick). */
static inline void gif_xyz2(struct gif *g, unsigned x, unsigned y, uint32_t z, int adc)
{
    gif_qword(g, (uint64_t)x | (uint64_t)y << 32, (uint64_t)z | (uint64_t)(adc & 1) << 47);
}

static inline void gif_uv(struct gif *g, unsigned u, unsigned v)
{
    gif_qword(g, (uint64_t)u | (uint64_t)v << 32, 0);
}

/* Register values. */
static inline uint64_t gs_prim(unsigned type, int iip, int tme, int fge, int abe, int fst, int ctxt)
{
    return (uint64_t)type | (uint64_t)iip << 3 | (uint64_t)tme << 4 | (uint64_t)fge << 5 | (uint64_t)abe << 6 |
        (uint64_t)fst << 8 | (uint64_t)ctxt << 9;
}

static inline uint64_t gs_frame(unsigned fbp, unsigned fbw, unsigned psm, uint32_t fbmsk)
{
    return (uint64_t)fbp | (uint64_t)fbw << 16 | (uint64_t)psm << 24 | (uint64_t)fbmsk << 32;
}

static inline uint64_t gs_scissor(unsigned x0, unsigned x1, unsigned y0, unsigned y1)
{
    return (uint64_t)x0 | (uint64_t)x1 << 16 | (uint64_t)y0 << 32 | (uint64_t)y1 << 48;
}

static inline uint64_t gs_xyoffset(unsigned x, unsigned y)
{
    return (uint64_t)x | (uint64_t)y << 32;
}

static inline uint64_t gs_tex0(unsigned tbp, unsigned tbw, unsigned psm, unsigned tw, unsigned th, int tcc, unsigned tfx,
    unsigned cbp, unsigned cpsm)
{
    return (uint64_t)tbp | (uint64_t)tbw << 14 | (uint64_t)psm << 20 | (uint64_t)tw << 26 | (uint64_t)th << 30 |
        (uint64_t)(tcc & 1) << 34 | (uint64_t)tfx << 35 | (uint64_t)cbp << 37 | (uint64_t)cpsm << 51;
}

static inline uint64_t gs_alpha(unsigned a, unsigned b, unsigned c, unsigned d, unsigned fix)
{
    return (uint64_t)a | (uint64_t)b << 2 | (uint64_t)c << 4 | (uint64_t)d << 6 | (uint64_t)fix << 32;
}

static inline uint64_t gs_bitbltbuf(unsigned dbp, unsigned dbw, unsigned dpsm)
{
    return (uint64_t)dbp << 32 | (uint64_t)dbw << 48 | (uint64_t)dpsm << 56;
}

static inline uint64_t gs_trxpos(unsigned sx, unsigned sy, unsigned dx, unsigned dy)
{
    return (uint64_t)sx | (uint64_t)sy << 16 | (uint64_t)dx << 32 | (uint64_t)dy << 48;
}

static inline uint64_t gs_trxreg(unsigned w, unsigned h)
{
    return (uint64_t)w | (uint64_t)h << 32;
}

#endif
