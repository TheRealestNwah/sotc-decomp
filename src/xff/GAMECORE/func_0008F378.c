#ifdef NONMATCHING
/* 105 diffs, same length (110 words). Draft from the asm; first of the func_0008F378 / 8F748 / 8F930 (+ 8FB18) stick-input shapers (likely the same code with other constants). Takes an input pair (x, y) and two scale args (a, b): clamps the max/min of x to +-1.0 and of y to +-0.9, gets a dist ratio for y (positive: ratio(y, 0.0436 * b, hi); negative: 1 - ratio(y, lo, -0.0436 * b)), raises it to 1.5 with powf, builds the matching ratio for x, and when it is below the y one interpolates x with GAMEUTIL_get_interp_value before calling func_0008E918(obj, x, y, a, b). Difference is register pressure: the Original saves $f20..$f28 (frame 0x70) because a and b stay live in $f28/$f27 and the clamp constants sit in $f24..$f26; ours saves $f20..$f27 (frame 0x60) and loads some constants later. Permuter (12 workers, 12 min): 4855 -> 4550. */
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);
extern float powf(float, float);
extern void func_0008E918(void *, float, float, float, float);

void func_0008F378(void *obj, float x, float y, float a, float b)
{
    float st[2];
    float hx = a * 0.04363323003053665f;
    float hy = b * 0.04363323003053665f;
    float maxX = 1.0f;
    float minX = -1.0f;
    float hi = 0.9f;
    float lo = -0.9f;
    float r;
    float p;
    float q;

    st[0] = x;
    st[1] = y;
    if (1.0f < x)
        maxX = x;
    if (x < -1.0f)
        minX = x;
    if (0.9f < y)
        hi = y;
    if (y < -0.9f)
        lo = y;
    if (0.0f <= y)
        r = GAMEUTIL_get_dist_ratio(y, hy, hi);
    else
        r = 1.0f - GAMEUTIL_get_dist_ratio(y, lo, -hy);
    p = powf(r, 1.5f);
    if (0.0f <= x)
        q = 1.0f - GAMEUTIL_get_dist_ratio(x, hx, maxX);
    else
        q = GAMEUTIL_get_dist_ratio(x, minX, -hx);
    if (q < p)
        st[0] = GAMEUTIL_get_interp_value(0.0f <= x ? hx : -hx, x, p - q);
    func_0008E918(obj, st[0], y, a, b);
}
#endif
