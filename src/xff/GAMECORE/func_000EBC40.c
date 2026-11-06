extern void constructor_nico_yaw_pitch_cntrl(void *);
extern void func_000E95E0(void *);

static void func_000EBC40(int *a)
{
    *a = 0;
    constructor_nico_yaw_pitch_cntrl(a + 1);
}

static void func_000EBC60(void *a)
{
    func_000E95E0(a);
}

static void func_000EBC78(void *a)
{
    func_000E95E0(a);
}

static void func_000EBC90(char *dst, char *src)
{
    *(char **)(dst + 0x1370) = src + 0x4C;
    *(char **)(dst + 0x2C44) = src + 0x1E0;
    *(char **)(dst + 0x2D20) = src + 0x2AC;
    *(char **)(dst + 0x2DE0) = src + 0x330;
    *(char **)(dst + 0x2ED0) = src + 0x400;
    *(char **)(dst + 0x2FF0) = src + 0x4E4;
    *(char **)(dst + 0x3120) = src + 0x5C8;
}

extern void constructor_game_camera_param_update_data_manager(void *);
extern void func_000E5268(void *, void *, char *, char *, void *);
extern void doit_game_camera_param_manager(char *, void *, void *, char *, float);
extern void get_game_camera_mode_local_parameter(char *, char *);
extern int func_000E9AA0(void *, void *, void *, int);
extern int is_main_type_camera_lws_animation_update(void *);

static void func_000EBE88(void *a, void *b, void *c)
{
    func_000E9AA0(a, b, c, 0);
}

#ifdef NONMATCHING
static int func_000EBEA0(void *a, void *b, void *c)
{
    int v = is_main_type_camera_lws_animation_update(a);

    return func_000E9AA0(a, b, c, v);
}
#endif

extern float func_000ECCE8(char *);
extern float func_000E6B00(void *);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);
extern void reset_double_spring_interp_cntrl(char *, float);
extern void doit_double_spring_interp_cntrl(char *, float, int, float);

static int func_000EBEF0(char *c)
{
    char *s = c + 0x3270;
    int m = *(int *)(c + 0x1360);

    if (m != 7)
        s = m == 8 ? c + 0x34E0 : 0;
    if (m == 0 || (s != 0 && (*(int *)(s + 0x8C) == 0 || *(int *)(s + 0x8C) == 2 || *(int *)(s + 0x98) != 0)))
        return 1;
    return 0;
}

#ifdef NONMATCHING
static void func_000EBF58(char *o, char *c, int flag)
{
    char *s = c + 0x3270;
    int m = *(int *)(c + 0x1360);
    float t;

    if (m != 7)
        s = m == 8 ? c + 0x34E0 : 0;
    if (s != 0)
        t = func_000ECCE8(s);
    else
        t = func_000E6B00(o);
    set_param_double_spring_interp_common(o + 0x1A4, *(float *)(*(char **)o + 0x174), *(float *)(*(char **)o + 0x17C),
                                          *(float *)(*(char **)o + 0x178), -1.0f);
    if (flag != 0 || s != 0)
        reset_double_spring_interp_cntrl(o + 0x1A4, t);
    else
        doit_double_spring_interp_cntrl(o + 0x1A4, t, 0, D_0017B720);
}
#endif
