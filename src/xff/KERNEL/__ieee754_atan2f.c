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

#define FLT_UWORD_IS_FINITE(x) 1
#define FLT_UWORD_IS_NAN(x) 0
#define FLT_UWORD_IS_INFINITE(x) 0
#define FLT_UWORD_IS_ZERO(x) ((x) < 0x00800000L)
#define FLT_UWORD_IS_SUBNORMAL(x) 0

extern float atanf(float x);
extern float fabsf(float x);

#define tiny (1.0e-30f)
#define zero (0.0f)
#define pi_o_4 (7.8539818525e-01f) /* 0x3f490fdb */
#define pi_o_2 (1.5707963705e+00f) /* 0x3fc90fdb */
#define pi (3.1415925026e+00f) /* 0x40490fda */
#define pi_lo (1.5099578832e-07f) /* 0x34222168 */

float __ieee754_atan2f(float y, float x)
{
    float z;
    int k, m, hx, hy, ix, iy;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    GET_FLOAT_WORD(hy, y);
    iy = hy & 0x7fffffff;
    if (FLT_UWORD_IS_NAN(ix) || FLT_UWORD_IS_NAN(iy)) {
        return x + y; /* x or y is NaN */
    }
    if (hx == 0x3f800000) {
        return atanf(y); /* x=1.0 */
    }
    m = ((hy >> 31) & 1) | ((hx >> 30) & 2); /* 2*sign(x)+sign(y) */

    /* when y = 0 */
    if (FLT_UWORD_IS_ZERO(iy)) {
        switch (m) {
        case 0:
        case 1:
            return y; /* atan(+-0,+anything)=+-0 */
        case 2:
            return pi + tiny; /* atan(+0,-anything) = pi */
        case 3:
            return -pi - tiny; /* atan(-0,-anything) =-pi */
        }
    }
    /* when x = 0 */
    if (FLT_UWORD_IS_ZERO(ix)) {
        return (hy < 0) ? -pi_o_2 - tiny : pi_o_2 + tiny;
    }

    /* when x is INF */
    if (FLT_UWORD_IS_INFINITE(ix)) {
        if (FLT_UWORD_IS_INFINITE(iy)) {
            switch (m) {
            case 0:
                return pi_o_4 + tiny; /* atan(+INF,+INF) */
            case 1:
                return -pi_o_4 - tiny; /* atan(-INF,+INF) */
            case 2:
                return (float)3.0 * pi_o_4 + tiny; /* atan(+INF,-INF) */
            case 3:
                return (float)-3.0 * pi_o_4 - tiny; /* atan(-INF,-INF) */
            }
        } else {
            switch (m) {
            case 0:
                return zero; /* atan(+...,+INF) */
            case 1:
                return -zero; /* atan(-...,+INF) */
            case 2:
                return pi + tiny; /* atan(+...,-INF) */
            case 3:
                return -pi - tiny; /* atan(-...,-INF) */
            }
        }
    }
    /* when y is INF */
    if (FLT_UWORD_IS_INFINITE(iy)) {
        return (hy < 0) ? -pi_o_2 - tiny : pi_o_2 + tiny;
    }

    /* compute y/x */
    k = (iy - ix) >> 23;
    if (k > 60) {
        z = pi_o_2 + (float)0.5 * pi_lo; /* |y/x| >  2**60 */
    } else if (hx < 0 && k < -60) {
        z = 0.0f; /* |y|/x < -2**60 */
    } else {
        z = atanf(fabsf(y / x)); /* safe to do y/x */
    }
    switch (m) {
    case 0:
        return z; /* atan(+,+) */
    case 1: {
        unsigned int zh;
        GET_FLOAT_WORD(zh, z);
        SET_FLOAT_WORD(z, zh ^ 0x80000000);
    }
        return z; /* atan(-,+) */
    case 2:
        return pi - (z - pi_lo); /* atan(+,-) */
    default: /* case 3 */
        return (z - pi_lo) - pi; /* atan(-,-) */
    }
}
