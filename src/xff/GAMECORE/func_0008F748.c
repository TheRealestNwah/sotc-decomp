/* Parked draft: stick-input dead-zone/shaping step. Clamps the two stick axes to the extended range
   (+-1.2 on x, +-1 on y), normalises each against the dead zone (axis * 5 degrees in radians),
   raises the y ratio to 1.5, and when the x ratio is below it replaces x by an interpolation toward
   the dead-zone edge; then hands the pair to func_0008E918. Written from the m2c draft; not yet
   compared closely. */
#ifdef NONMATCHING
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);
extern void func_0008E918(int, float, float, float, float);
extern float powf(float, float);

static void func_0008F748(int ctx, float x, float y, float zx, float zy)
{
    float v[2];
    float *p = v;
    float dzx = zx * 0.0872664601f;
    float dzy = zy * 0.0872664601f;
    float ndz = -dzx;
    float ndzy = -dzy;
    float xmax = 1.2f;
    float xmin = -1.2f;
    float ymax = 1.0f;
    float ymin = -1.0f;
    float ry;
    float rx;
    float shaped;

    v[1] = y;
    v[0] = x;
    if (x > 1.2f)
        xmax = x;
    if (x < -1.2f)
        xmin = x;
    if (y > 1.0f)
        ymax = y;
    if (y < -1.0f)
        ymin = y;
    if (y >= 0.0f)
        ry = GAMEUTIL_get_dist_ratio(y, dzy, ymax);
    else
        ry = 1.0f - GAMEUTIL_get_dist_ratio(y, ymin, ndzy);
    shaped = powf(ry, 1.5f);
    if (x >= 0.0f)
        rx = 1.0f - GAMEUTIL_get_dist_ratio(x, dzx, xmax);
    else
        rx = GAMEUTIL_get_dist_ratio(x, xmin, ndz);
    if (rx < shaped) {
        float edge;
        if (x >= 0.0f)
            edge = dzx;
        else
            edge = ndz;
        p[0] = GAMEUTIL_get_interp_value(edge, x, shaped - rx);
    } else {
        p[0] = x;
    }
    v[1] = y;
    func_0008E918(ctx, v[0], y, zx, zy);
}
#endif
