typedef unsigned int u_long128 __attribute__((mode(TI)));

extern int *DldSysUndefSymbol;
extern char D_0017B620[];
extern char D_0017B660[];
extern u_long128 D_0017B670;
extern char IdentityQuaternion[];
extern char ZeroPoint[];
extern void *CAM_get_target_obj(void *);
extern char *GetLayoutClass(void *);
extern void SetGeometryPointerGlobalStatePointer(void *, void *, void *, void *, void *);
extern int is_base_mode_manager_update_game_camera_param_manager(void *);
extern int is_same_camera_lws_animation(int, void *);
extern void end_camera_lws_animation(int);
extern int boot_camera_lws_animation(void *, void *, int, int, int, float);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static void func_000D8380(int *anim, char *cam, char *mgr)
{
    char *layout;
    char *lws;

    layout = GetLayoutClass(CAM_get_target_obj(cam + 0x23C));
    D_0017B670 = **(u_long128 **)(layout + 0x134);
    SetGeometryPointerGlobalStatePointer(D_0017B620, D_0017B660, &D_0017B670, IdentityQuaternion, ZeroPoint);
    if (is_base_mode_manager_update_game_camera_param_manager(mgr + 0x50) != 1)
        return;
    lws = dldResolve(*(unsigned int **)(*(char **)cam + 0x14));
    if (is_same_camera_lws_animation(*anim, lws))
        return;
    end_camera_lws_animation(*anim);
    *anim = boot_camera_lws_animation(lws, D_0017B620, 0, 0, 0, 0);
}
