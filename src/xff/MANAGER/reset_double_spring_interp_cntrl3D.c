float *reset_double_spring_interp_cntrl3D(char *p, float *v)
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
