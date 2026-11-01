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

extern float copysignf(float x, float y);

#define two25 (3.355443200e+07f)
#define twom25 (2.9802322388e-08f)
#define huge (1.0e+30f)
#define tiny (1.0e-30f)

float scalbnf(float x, int n)
{
    int k, ix;
    unsigned int hx;

    GET_FLOAT_WORD(ix, x);
    hx = ix & 0x7fffffff;
    k = hx >> 23; /* extract exponent */
    if (hx < 0x00800000) {
        return x;
    }
    k = k + n;
    if (k > 0xff) {
        return huge * copysignf(huge, x); /* overflow */
    }
    if (k > 0) {
        /* normal result */
        SET_FLOAT_WORD(x, (ix & 0x807fffff) | (k << 23));
        return x;
    }
    if (n > 50000) {
        /* in case integer overflow in n+k */
        return huge * copysignf(huge, x); /* overflow */
    } else {
        return tiny * copysignf(tiny, x); /* underflow */
    }
}
