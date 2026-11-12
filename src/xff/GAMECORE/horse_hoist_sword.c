/* Piecewise blend in double precision (soft-float on the R5900): knots at -0.5, 0 and 0.5 on x,
   each side mixing a linear term with a quadratic ease, plus an offset term from y. */
float horse_hoist_sword(float c0, float c1, float c2, float c3, float c4, float c5, float x, float y)
{
    double tail;
    double u;
    double a;
    double r;
    float f;

    if (y >= 0.0f)
        f = y * c4;
    else
        f = -(y * c5);
    tail = f;
    if (x >= 0.0f) {
        double xd = x;
        if (xd < 0.5) {
            r = 2.0f * (x * c0) + tail;
        } else {
            a = 2.0f * (x * c0);
            u = (xd - 0.5) * 2.0;
            r = a * (1.0 - u) + u * (double)(x * c1) + tail;
        }
    } else {
        double xd = x;
        if (xd > -0.5) {
            r = 2.0f * (x * -c2) + tail;
        } else {
            a = 2.0f * (x * -c2);
            u = (xd + 0.5) * 2.0;
            r = a * (u + 1.0) - u * (double)(x * -c3) + tail;
        }
    }
    return r;
}
