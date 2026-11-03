typedef union {
    float value;
    unsigned int word;
} ieee_float_shape_type;

#define GET_FLOAT_WORD(i, d)            \
    do {                                \
        ieee_float_shape_type gf_u;     \
        gf_u.value = (d);               \
        (i) = gf_u.word;                \
    } while (0)

#define SET_FLOAT_WORD(d, i)            \
    do {                                \
        ieee_float_shape_type sf_u;     \
        sf_u.word = (i);                \
        (d) = sf_u.value;               \
    } while (0)

extern const float RO_00141EA0[2];
#define TWO23 RO_00141EA0

float rintf(float x)
{
    int i0, j0, sx;
    unsigned int i, i1, ix;
    float t;
    volatile float w;

    GET_FLOAT_WORD(i0, x);
    sx = (i0 >> 31) & 1;
    ix = (i0 & 0x7fffffff);
    j0 = (ix >> 23) - 0x7f;
    if (j0 < 23) {
        if (ix < 0x00800000) {
            return x;
        }
        if (j0 < 0) {
            i1 = (i0 & 0x07fffff);
            i0 &= 0xfff00000;
            i0 |= ((i1 | -i1) >> 9) & 0x400000;
            SET_FLOAT_WORD(x, i0);
            w = TWO23[sx] + x;
            t = w - TWO23[sx];
            GET_FLOAT_WORD(i0, t);
            SET_FLOAT_WORD(t, (i0 & 0x7fffffff) | (sx << 31));
            return t;
        } else {
            i = (0x007fffff) >> j0;
            if ((i0 & i) == 0) {
                return x;
            }
            i >>= 1;
            if ((i0 & i) != 0) {
                i0 = (i0 & (~i)) | ((0x100000) >> j0);
            }
        }
    } else {
        return x;
    }
    SET_FLOAT_WORD(x, i0);
    w = TWO23[sx] + x;
    return w - TWO23[sx];
}
