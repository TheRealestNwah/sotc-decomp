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

#define one (1.0000000000e+00f)
#define C1 (4.1666667908e-02f) /* 0x3d2aaaab */
#define C2 (-1.3888889225e-03f) /* 0xbab60b61 */
#define C3 (2.4801587642e-05f) /* 0x37d00d01 */
#define C4 (-2.7557314297e-07f) /* 0xb493f27c */
#define C5 (2.0875723372e-09f) /* 0x310f74f6 */
#define C6 (-1.1359647598e-11f) /* 0xad47d74e */

float __kernel_cosf(float x, float y)
{
    float a, hz, z, r, qx;
    int ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff; /* ix = |x|'s high word */
    if (ix < 0x32000000) {
        /* if x < 2**27 */
        if (((int)x) == 0) {
            return one; /* generate inexact */
        }
    }
    z = x * x;
    r = z * (C1 + z * (C2 + z * (C3 + z * (C4 + z * (C5 + z * C6)))));
    if (ix < 0x3e99999a) {
        /* if |x| < 0.3 */
        return one - ((float)0.5 * z - (z * r - x * y));
    } else {
        if (ix > 0x3f480000) {
            /* x > 0.78125 */
            qx = (float)0.28125;
        } else {
            SET_FLOAT_WORD(qx, ix - 0x01000000); /* x/4 */
        }
        hz = (float)0.5 * z - qx;
        a = one - qx;
        return a - (hz - (z * r - x * y));
    }
}
