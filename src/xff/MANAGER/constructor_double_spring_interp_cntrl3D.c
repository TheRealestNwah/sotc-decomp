extern void set_param_double_spring_interp_common(char *, float, float, float, float);

void constructor_double_spring_interp_cntrl3D(char *p, float a, float b)
{
    float *x = (float *)(p + 0x14);
    float *y = (float *)(p + 0x20);
    int *z = (int *)(p + 0x30);
    int i;

    for (i = 0; i < 3; i++) {
        x[i] = 0.0f;
        y[i] = 0.0f;
        z[i] = 0;
    }
    set_param_double_spring_interp_common(p, 2.0f, -1.0f, 1.0f, -1.0f);
    *(float *)(p + 0x10) = a;
    *(float *)(p + 0x3C) = b;
    *(float *)(p + 0x2C) = b;
}
