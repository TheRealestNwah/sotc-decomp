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

#define huge (1.0e30f)

float floorf(float x)
{
    int i0, j0;
    unsigned int i, ix;

    GET_FLOAT_WORD(i0, x);
    ix = (i0 & 0x7fffffff);
    j0 = (ix >> 23) - 0x7f;
    if (j0 < 23) {
        if (j0 < 0) {
            /* raise inexact if x != 0 */
            if (huge + x > (float)0.0) {
                /* return 0*sign(x) if |x|<1 */
                if (i0 >= 0) {
                    i0 = 0;
                } else if (!(ix < 0x00800000)) {
                    i0 = 0xbf800000;
                }
            }
        } else {
            i = (0x007fffff) >> j0;
            if ((i0 & i) == 0) {
                return x; /* x is integral */
            }
            if (huge + x > (float)0.0) {
                /* raise inexact flag */
                if (i0 < 0) {
                    i0 += (0x00800000) >> j0;
                }
                i0 &= (~i);
            }
        }
    } else {
        return x; /* x is integral */
    }
    SET_FLOAT_WORD(x, i0);
    return x;
}
