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


#define half (5.0000000000e-01f)
#define S1 (-1.6666667163e-01f) /* 0xbe2aaaab */
#define S2 (8.3333337680e-03f) /* 0x3c088889 */
#define S3 (-1.9841270114e-04f) /* 0xb9500d01 */
#define S4 (2.7557314297e-06f) /* 0x3638ef1b */
#define S5 (-2.5050759689e-08f) /* 0xb2d72f34 */
#define S6 (1.5896910177e-10f) /* 0x2f2ec9d3 */

float __kernel_sinf(float x, float y, int iy)
{
    float z, r, v;
    int ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff; /* high word of x */
    if (ix < 0x32000000) {
        /* |x| < 2**-27 */
        if ((int)x == 0) {
            return x; /* generate inexact */
        }
    }
    z = x * x;
    v = z * x;
    r = S2 + z * (S3 + z * (S4 + z * (S5 + z * S6)));
    if (iy == 0) {
        return x + v * (S1 + z * r);
    } else {
        return x - ((z * (half * y - v * r) - y) - v * S1);
    }
}
