extern char *get_cur_using_lws_anime_mode_base_class(void *);
extern int is_view_angle_exist_lws_anime_mode_base(void *);
extern void reset_double_spring_interp_cntrl(char *, float);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);
extern void doit_double_spring_interp_cntrl(char *, float, int, float);
extern void constructor_double_spring_interp_cntrl(char *, float);
extern float get_view_angle_lws_anime_mode_base(void *);
extern int is_view_angle_zoom_game_camera(void *);
extern char gcGlobalVar[];
extern float RO_001811D0;
extern char RO_001811B8[];
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void iosInitKPrintfContext(void *, float, float, int, int, float, float, float, float);
extern void iosSetKPrintfLocateContext(void *, float, float);
extern void kprintfContext(void *, const char *, ...);
typedef struct {
    char pad0[0x1C];
    void *chara;
    char pad20[0x37C4 - 0x20];
    float timer;
} DispWork;

static float func_000E2B88(int mode, char *p, void *lws);
static float func_000E2BB8(int which, char *cam, char *p);

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

void constructor_camera_view_angle_cntrl(char *c)
{
    char *s = c + 0x20;
    constructor_double_spring_interp_cntrl(c, 0.001f);
    reset_double_spring_interp_cntrl(c, 45.0f);
    constructor_double_spring_interp_cntrl(s, 0.0001f);
    reset_double_spring_interp_cntrl(s, 1.0f);
}

float get_view_angle_camera_view_angle_cntrl(void *arg0)
{
    return (*(float *)((char *)(arg0) + 0x1C));
}

static float func_000E2B88(int mode, char *p, void *lws)
{
    if (mode == 1) {
        return get_view_angle_lws_anime_mode_base(lws);
    }
    return *(float *)(p + 0x4C);
}

static float func_000E2BB8(int which, char *cam, char *p)
{
    float r = 1.0f;
    int z = is_view_angle_zoom_game_camera(cam);

    if (z == 1) {
        if (which == z)
            r = *(float *)(p + 0xB4);
        else
            r = *(float *)(cam + 0x13C0);
    }
    return r;
}

static void func_000E2C20(DispWork *w, int reset)
{
    char ctx[0x40];

    if (reset)
        w->timer = 2.0f;
    else
        w->timer -= *(float *)(gcGlobalVar + 0x170);
    if (0.0f < w->timer) {
        float x, y;
        iosDlPushLayer(3);
        x = getDrawScreenWidth() * -0.2f;
        y = getDrawScreenHeight() * RO_001811D0;
        if (GetCharacterClass(w->chara))
            iosInitKPrintfContext(ctx, x, y, 0, 1, 0.6f, 0.6f, 1.0f, 1.0f);
        else
            iosInitKPrintfContext(ctx, x, y, 0, 1, 1.0f, 0.6f, 0.6f, 1.0f);
        iosSetKPrintfLocateContext(ctx, x, y);
        kprintfContext(ctx, RO_001811B8, *(int *)(GetLayoutClass(w->chara) + 0x130));
        iosDlPopLayer();
    }
}
