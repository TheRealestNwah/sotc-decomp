#ifdef NONMATCHING /* 2 diffs: the two mov.s zero-inits of b and c come out swapped */
int GAMEUTIL_get_cross_position_coefficient_t_by_dist_factor(float dist, float *t0, float *t1, float *p, float *q, float *r)
{
    float a, b, c;
    float d;
    float s;
    float e;
    int i;
    int ok;

    b = c = a = 0.0f;
    for (i = 0; i < 3; i++) {
        float u = r[i] - q[i];
        float v = q[i] - p[i];
        c += v * v;
        a += u * u;
        b += (u + u) * v;
    }
    c -= dist * dist;
    d = b * b - a * 4.0f * c;
    ok = 1;
    if (d < 0.0f) {
        ok = 0;
    }
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(d) : "f"(d)); s = d;
    *t0 = (s - b) / (a + a);
    *t1 = (-b - s) / (a + a);
    e = *t0;
    if (e < *t1) {
        *t0 = *t1;
        *t1 = e;
    }
    return ok;
}
#endif
