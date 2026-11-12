extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);
extern float powf(float, float);
extern void func_0008E918(int, float, float, float, float);

#ifdef NONMATCHING /* 107 diffs: float register numbering (hx*K and the powf result swap f22/f23) and s0/s1 swap for the pointer-to-locals vs the first argument */
static void func_0008FB18(int a0, float x, float y, float hx, float hy)
{
    float v[2];
    float *pv = v;
    int ar = a0;
    float hxr = hx * 0.0872664675f;
    float hyr = hy * 0.0872664675f;
    float nhx = -hxr;
    float xmax = 1.2f;
    float xmin = -1.2f;
    float ymax = 1.0f;
    float ymin = -1.0f;
    float ry;
    float rx;
    float e;

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
        ry = 1.0f - GAMEUTIL_get_dist_ratio(y, ymin, -hyr);
    e = powf(ry, 1.5f);
    if (x >= 0.0f)
        rx = 1.0f - GAMEUTIL_get_dist_ratio(x, hxr, xmax);
    else
        rx = GAMEUTIL_get_dist_ratio(x, xmin, nhx);
    if (rx < e)
        *pv = GAMEUTIL_get_interp_value(x >= 0.0f ? hxr : nhx, x, e - rx);
    else
        *pv = x;
    v[1] = y;
    func_0008E918(ar, v[0], y, hx, hy);
}
#endif
