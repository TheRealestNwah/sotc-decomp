extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);
extern float powf(float, float);
extern void func_0008E918(int, float, float, float, float);

#ifdef NONMATCHING /* 56 diffs: hx/hy pinned to f28/f27 and hx*K to f23, the locals pointer and first argument pinned to s0/s1, negated halves as locals. Remaining: the Original stores v[0]/v[1] straight from the argument registers (v[0] in the bc1f delay slot), hoists the 0.0f compare constant into f1 with hy*K in f2, saves callee registers in another order, lays the final ternary out as bc1t/b with unreachable nops, and calls func_0008E918 section-relative */
static void func_0008FB18(int a0, float x, float y, float hx0, float hy0)
{
    register float hx __asm__("$f28") = hx0;
    register float hy __asm__("$f27") = hy0;
    float v[2];
    register float *pv __asm__("$16") = v;
    register int ar __asm__("$17") = a0;
    register float hxr __asm__("$f23") = hx * 0.0872664675f;
    float hyr = hy * 0.0872664675f;
    float nhy = -hyr;
    float nhx = -hxr;
    float xmax = 1.2f;
    float xmin = -1.2f;
    float ymax = 1.0f;
    float ymin = -1.0f;
    float ry;
    float rx;
    register float e __asm__("$f22");

    v[0] = x;
    v[1] = y;
    if (x > xmax)
        xmax = x;
    if (x < xmin)
        xmin = x;
    if (y > ymax)
        ymax = y;
    if (y < ymin)
        ymin = y;
    if (y >= 0.0f)
        ry = GAMEUTIL_get_dist_ratio(y, hyr, ymax);
    else
        ry = 1.0f - GAMEUTIL_get_dist_ratio(y, ymin, nhy);
    e = powf(ry, 1.5f);
    if (x >= 0.0f)
        rx = 1.0f - GAMEUTIL_get_dist_ratio(x, hxr, xmax);
    else
        rx = GAMEUTIL_get_dist_ratio(x, xmin, nhx);
    if (rx < e) {
        float d = e - rx;
        *pv = GAMEUTIL_get_interp_value(x >= 0.0f ? hxr : nhx, x, d);
    }
    else
        *pv = x;
    v[1] = y;
    func_0008E918(ar, v[0], y, hx, hy);
}
#endif
