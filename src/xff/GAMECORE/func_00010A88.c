extern int *DldSysUndefSymbol;
extern char InitialGeometryPointer[];
extern int GetMotionResourceFrames(void *);
extern int end_camera_lws_animation(int);
extern void DisplayCaptionTableChild(void *, void *, int);
extern void fsEffectManagerSetDemoParam(void *);
extern int boot_camera_lws_animation(void *, void *, int, int, int, float);

typedef union {
    float f[3];
    int i[3];
} Vec3U;

typedef struct {
    float arg;
    void (*func)(float);
} DemoCallback;

typedef struct {
    unsigned int pad0;
    unsigned int lws;
    unsigned int caption;
    unsigned int effect;
    DemoCallback callbacks[2];
} DemoCameraRes;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static int func_00010A88(int *anim, DemoCameraRes *res, char *obj, void *caption)
{
    float *pos = (float *)(obj + 0x10);
    char *lws = dldResolve(&res->lws);
    int frames = GetMotionResourceFrames(lws + 4);
    int i;
    DemoCallback *cb;

    ((Vec3U *)(lws + 0xBC))->f[0] = pos[0];
    ((Vec3U *)(lws + 0xBC))->f[1] = pos[1];
    ((Vec3U *)(lws + 0xBC))->f[2] = pos[2];
    if (*anim >= 0) {
        end_camera_lws_animation(*anim);
        *anim = -1;
    }
    if (dldResolve(&res->caption) != 0)
        DisplayCaptionTableChild(&res->caption, caption, 2);
    fsEffectManagerSetDemoParam(dldResolve(&res->effect));
    *anim = boot_camera_lws_animation(lws, InitialGeometryPointer, 0, 0, 0, 0.0f);
    cb = res->callbacks;
    for (i = 1; i != -1; i--, cb++) {
        if (cb->func != 0)
            cb->func(cb->arg);
    }
    return frames;
}
