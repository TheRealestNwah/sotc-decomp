extern void GAMEUTIL_get_spring_interpolate_value3D_extend(float, float, float, float *, float *, float *, float *, float);

static inline float *reset_double_spring_interp_cntrl3D(char *p, float *v)
{
    float *b = (float *)(p + 0x20);
    float *a = (float *)(p + 0x30);
    int i;
    for (i = 0; i < 3; i++) {
        float f = v[i];
        a[i] = f;
        b[i] = f;
    }
    return a;
}

float *doit_double_spring_interp_cntrl3D(char *p, float *target, int reset, float rate)
{
    float *mid;
    float *vel;
    float *out;

    if (reset == 1) {
        return reset_double_spring_interp_cntrl3D(p, target);
    }
    mid = (float *)(p + 0x20);
    vel = (float *)(p + 0x14);
    out = (float *)(p + 0x30);
    GAMEUTIL_get_spring_interpolate_value3D_extend(*(float *)(p + 0x0), *(float *)(p + 0x4), *(float *)(p + 0x10), mid, mid, target, vel, rate);
    GAMEUTIL_get_spring_interpolate_value3D_extend(*(float *)(p + 0x8), *(float *)(p + 0xC), *(float *)(p + 0x10), out, out, mid, vel, rate);
    return out;
}
