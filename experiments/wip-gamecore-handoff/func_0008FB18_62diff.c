extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);
extern float powf(float, float);
extern void func_0008E918(void *, float, float, float, float);

static void func_0008FB18(void *a, float x, float y, float p, float q)
{
    float v[2];
    float *pv = v;
    float npx, nqx;
    float px, qx, xmax, xmin, ymax, ymin, r, s;

    v[0] = x;
    v[1] = y;
    px = p * 0.087266462f;
    qx = q * 0.087266462f;
    npx = -px;
    nqx = -qx;
    xmax = 1.2f;
    xmin = -1.2f;
    ymax = 1.0f;
    ymin = -1.0f;
    if (xmax < x)
        xmax = x;
    if (x < xmin)
        xmin = x;
    if (ymax < y)
        ymax = y;
    if (y < ymin)
        ymin = y;
    if (0.0f <= y)
        r = GAMEUTIL_get_dist_ratio(y, qx, ymax);
    else
        r = 1.0f - GAMEUTIL_get_dist_ratio(y, ymin, nqx);
    r = powf(r, 1.5f);
    if (0.0f <= x)
        s = 1.0f - GAMEUTIL_get_dist_ratio(x, px, xmax);
    else
        s = GAMEUTIL_get_dist_ratio(x, xmin, npx);
    if (s < r)
        pv[0] = GAMEUTIL_get_interp_value(0.0f <= x ? px : npx, x, r - s);
    else
        pv[0] = x;
    pv[1] = y;
    func_0008E918(a, v[0], v[1], p, q);
}
