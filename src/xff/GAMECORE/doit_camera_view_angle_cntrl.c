extern char *get_cur_using_lws_anime_mode_base_class(void *);
extern int is_view_angle_exist_lws_anime_mode_base(void *);
extern float func_000E2B88(int, char *, void *);
extern float func_000E2BB8(int, void *, void *);
extern void reset_double_spring_interp_cntrl(char *, float);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);
extern void doit_double_spring_interp_cntrl(char *, float, int, float);

void doit_camera_view_angle_cntrl(char *cntrl, char *cam, int flag, float dt)
{
    char *s2 = cam + 0x1370;
    void *base = get_cur_using_lws_anime_mode_base_class(cam);
    int exists = 0;
    float v;
    float f20;
    float f21;
    char *p;

    if (base != 0)
        exists = is_view_angle_exist_lws_anime_mode_base(base);
    if (flag == 1) {
        reset_double_spring_interp_cntrl(cntrl, func_000E2B88(exists, s2, base));
        reset_double_spring_interp_cntrl(cntrl + 0x20, 1.0f);
    } else {
        f21 = func_000E2B88(exists, s2, base);
        f20 = func_000E2BB8(exists, cam, base);
        p = *(char **)s2;
        if (exists == 1) {
            set_param_double_spring_interp_common(cntrl + 0x20, *(float *)(p + 0x154), *(float *)(p + 0x15C), *(float *)(p + 0x158), -1.0f);
            doit_double_spring_interp_cntrl(cntrl + 0x20, f20, 0, dt);
            reset_double_spring_interp_cntrl(cntrl, *(float *)(cntrl + 0x3C) * f21);
            } else {
            set_param_double_spring_interp_common(cntrl, *(float *)(p + 0x154), *(float *)(p + 0x15C), *(float *)(p + 0x158), -1.0f);
            doit_double_spring_interp_cntrl(cntrl, f20 * f21, 0, dt);
            reset_double_spring_interp_cntrl(cntrl + 0x20, 1.0f);
            }
    }
    v = *(float *)(cntrl + 0x1C);
    if (v < 1.0f)
        reset_double_spring_interp_cntrl(cntrl, 1.0f);
    else if (179.0f < v)
        reset_double_spring_interp_cntrl(cntrl, 179.0f);
}
