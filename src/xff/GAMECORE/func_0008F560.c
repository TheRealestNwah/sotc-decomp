/* Parked: 92 differing words (float scheduling/regalloc); permuter best 2585 from base 3985.
   Siblings func_0008F748 and func_0008F930 have identical bodies. */
#ifdef NONMATCHING
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);
extern void func_0008E918(int, float, float, float, float);
extern float powf(float, float);

void func_0008F560(int arg0, float a, float b, float c, float d)
{
    float v[2]; float *p = v;
    float t2n, t22, t23, t26, t2, f25, f24, f14, f13, f0, f1, f12;
    f25 = 1.2f;
    t23 = c * 0.0872664626f;
    t2 = d * 0.0872664626f;
    v[1] = b;
    t26 = -t23;
    t2n = -t2;
    f24 = -1.2f;
    f14 = 1.0f;
    f13 = -1.0f;
    v[0] = a;
    if (a > 1.2f) f25 = a;
    if (a < -1.2f) f24 = a;
    if (b > 1.0f) f14 = b;
    if (b < -1.0f) f13 = b;
    if (!(b >= 0.0f))
        f0 = 1.0f - GAMEUTIL_get_dist_ratio(b, f13, t2n);
    else
        f0 = GAMEUTIL_get_dist_ratio(b, t2, f14);
    t22 = powf(f0, 1.5f);
    if (!(a >= 0.0f))
        f1 = GAMEUTIL_get_dist_ratio(a, f24, t26);
    else
        f1 = 1.0f - GAMEUTIL_get_dist_ratio(a, t23, f25);
    if (!(f1 < t22)) {
        *p = a;
    } else {
        if (!(a >= 0.0f)) f12 = t26; else f12 = t23;
        *p = GAMEUTIL_get_interp_value(f12, a, t22 - f1);
    }
    v[1] = b;
    func_0008E918(arg0, v[0], v[1], c, d);
}
#endif
