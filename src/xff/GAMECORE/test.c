/* Parked draft (identical code to horse_hoist_sword): piecewise blend in double precision (soft-float dpadd/dpmul/dpsub/dpcmp on the
   R5900; plain `double` in C). x is the sample position with knots at -0.5, 0 and 0.5; each side
   mixes a linear term (position times a coefficient float) with a quadratic ease; y adds an
   offset term. The result is returned as a float (dptofp). Written from the m2c draft; not yet
   compared closely. */
#ifdef NONMATCHING
float test(float c0, float c1, float c2, float c3, float c4, float c5, float x, float y)
{
    double tail;
    double t;
    double u;
    float f;
    double r;

    if (y >= 0.0f)
        f = y * c4;
    else
        f = -(y * c5);
    tail = f;
    if (x >= 0.0f) {
        double xd = x;
        f = x * c0;
        if (xd >= 0.5) {
            double v = xd - 0.5;
            u = v + v;
            t = (double)(2.0f * f) * (1.0 - u);
            r = t + u * (double)(x * c1);
        } else {
            r = (double)(2.0f * f);
        }
    } else {
        double xd = x;
        float nc2 = -c2;
        if (xd > -0.5) {
            f = x * nc2;
            r = (double)(2.0f * f);
        } else {
            double v = xd + 0.5;
            u = v + v;
            t = (double)(2.0f * (x * nc2)) * (u + 1.0);
            r = t - u * (double)(x * -c3);
        }
    }
    return (float)(r + tail);
}
#endif
