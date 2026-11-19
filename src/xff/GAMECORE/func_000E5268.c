extern int *DldSysUndefSymbol;
extern float D_0017B720;
extern int SCameraModeConditionParam_INSURANCE[];
extern int get_manage_obj_status_camera_place_status(char *);
extern void doit_camera_etc_condition(char *, char *, void *, float);
extern char *get_camera_lws_animation_param(int);
extern void reset_game_camera_param_update_data_manager(void *, int);
extern void set_update_data_game_camera_param_update_data_manager(void *, int, void *, void *, char *, float);
extern int get_place_status_camera_place_status(char *);
extern int func_000E54E0(void *, char *, void *, int, int, char *, void *);
extern int func_000E5738(void *, char *, void *, int, int, char *, void *);
extern int func_000E5A10(void *, char *, void *, int, int, char *, void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

static int func_000E5268(void *mgr, char *a1, char *g, void *a3, void *t0)
{
    int done = 0;
    char *p;
    char *ps;
    int st;
    int i;
    int mode = *(int *)(g + 0x1360);

    if (mode == 7)
        p = g + 0x3270;
    else if (mode == 8)
        p = g + 0x34E0;
    else
        p = 0;
    ps = a1 + 0x1270;
    st = get_manage_obj_status_camera_place_status(ps);
    doit_camera_etc_condition(g + 0x10, g, t0, D_0017B720);
    if (p != 0 && *(int *)(p + 0x90) != 0) {
        char *q = dldResolve((unsigned int *)(get_camera_lws_animation_param(*(int *)(p + 0x90)) + 0x80));
        if (q != 0) {
            reset_game_camera_param_update_data_manager(mgr, 1);
            set_update_data_game_camera_param_update_data_manager(mgr, 0, q, a3, a1, 1.0f);
            done = 1;
        }
    }
    if (done == 0) {
        for (i = 2; i >= 0; i--) {
            int s = get_place_status_camera_place_status(ps);
            if (s == 0)
                done = func_000E54E0(mgr, a1, a3, i, st, g, t0);
            else if (s == 1)
                done = func_000E5738(mgr, a1, a3, i, st, g, t0);
            else if (s == 2)
                done = func_000E5A10(mgr, a1, a3, i, st, g, t0);
            if (done == 1)
                break;
        }
        if (done == 0) {
            int *sh = SCameraModeConditionParam_INSURANCE;
            if (sh != DldSysUndefSymbol) {
                reset_game_camera_param_update_data_manager(mgr, 1);
                set_update_data_game_camera_param_update_data_manager(mgr, 0, (void *)*sh, a3, a1, 1.0f);
            } else {
                __asm__ __volatile__("break 0");
            }
        }
    }
}
