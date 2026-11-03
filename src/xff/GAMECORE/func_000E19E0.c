typedef unsigned int u_long128 __attribute__((mode(TI)));

extern int CAM_is_need_obstacle_avoid_ofst(char *);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);
extern float doit_double_spring_interp_cntrl(char *, float, int, float);

static void func_000E19E0(u_long128 *out, char *w, u_long128 *src, int unused, char *a, char *cam, int c, float rate,
                          float dt)
{
    float v;
    char *sp = w + 0x40;

    v = 0.0f;
    if (CAM_is_need_obstacle_avoid_ofst(cam) == 1)
        v = rate * *(float *)(a + 0x175C) * *(float *)(*(char **)(cam + 0x2C44) + 0xAC);
    *out = *src;
    set_param_double_spring_interp_common(sp, 5.0f, -1.0f, 2.5f, -1.0f);
    ((float *)out)[1] += doit_double_spring_interp_cntrl(sp, v, c, dt);
}
