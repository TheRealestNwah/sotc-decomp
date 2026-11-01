float reset_double_spring_interp_cntrl(char *p, float v)
{
    float *b = (float *)(p + 0x18);
    float *a = (float *)(p + 0x1C);
    float t[1];
    int i;

    t[0] = v;
    for (i = 0; i < 1; i++) {
        float f = t[i];
        a[i] = f;
        b[i] = f;
    }
    return *a;
}
