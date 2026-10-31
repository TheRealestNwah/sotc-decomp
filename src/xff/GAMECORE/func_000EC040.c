extern float D_0017B720;
extern float func_000ECCF0(char *);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);
extern void reset_double_spring_interp_cntrl(char *, float);
extern float doit_double_spring_interp_cntrl(char *, float, float, int);
extern void ChangeGameTimeScaleRatio(float);

static void func_000EC040(char **o, char *c, int flag)
{
    char *s = c + 0x3270;
    int m = *(int *)(c + 0x1360);
    float t;

    if (m != 7)
        s = m == 8 ? c + 0x34E0 : 0;
    if (s != 0)
        t = func_000ECCF0(s);
    else
        t = *(float *)(*o + 0x18C);
    if (t < 0.099999997f)
        t = 0.099999997f;
    if (flag != 0 || s != 0) {
        reset_double_spring_interp_cntrl((char *)o + 0x208, t);
        ChangeGameTimeScaleRatio(t);
    } else {
        char *p = *o;

        set_param_double_spring_interp_common((char *)o + 0x208, *(float *)(p + 0x180), *(float *)(p + 0x188),
                                              *(float *)(p + 0x184), -1.0f);
        ChangeGameTimeScaleRatio(doit_double_spring_interp_cntrl((char *)o + 0x208, t, D_0017B720, 0));
    }
}
