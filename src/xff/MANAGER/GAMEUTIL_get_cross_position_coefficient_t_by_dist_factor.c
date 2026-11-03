#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
static inline float sqrt_s(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

int GAMEUTIL_get_cross_position_coefficient_t_by_dist_factor(float *t0, float *t1, float *p, float *q, float *r, float dist)
{
    float a = 0.0f, b = 0.0f, c = 0.0f;
    float d, e, disc, tmp;
    int i;
    int ret;

    for (i = 0; i < 3; i++) {
        d = r[i] - q[i];
        e = q[i] - p[i];
        a += d * d;
        b += 2.0f * d * e;
        c += e * e;
    }
    disc = b * b - 4.0f * a * (c - dist * dist);
    ret = !(disc < 0.0f);
    disc = sqrt_s(disc);
    *t0 = (disc - b) / (2.0f * a);
    *t1 = (-b - disc) / (2.0f * a);
    if (*t0 < *t1) {
        tmp = *t0;
        *t0 = *t1;
        *t1 = tmp;
    }
    return ret;
}
#endif
