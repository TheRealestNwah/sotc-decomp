typedef struct {
    long a[4];
    int id;
    int pad;
    long b[3];
} StageContext;

typedef void (*BoundaryCB)(StageContext *, StageContext *);

typedef struct {
    int kind;
    float near;
    float far;
    float density;
    float min;
    float max;
    int r;
    int g;
    int b;
    int a;
} FogInit;

typedef struct {
    char pad0[0x9C];
} LightParam;

typedef struct {
    char pad0[0x10];
    LightParam *lights;
} SheetSegHeader;

typedef struct {
    char pad0[0x20];
    int light;
} LightRef;

extern int D_0017A890;
extern BoundaryCB D_0017A898[2];
extern StageContext D_0017A8A0;
extern StageContext D_0017A8E0;
extern StageContext RO_0017CE40;
extern char RO_0017CE80[];
extern char rootPtn[];
extern void *get_main_cameraman(void);
extern void *get_cur_camera_target(void *);
extern char *iosgluGetCameraContext(void);
extern int GetStageContextByPos(StageContext *, void *);
extern char *GetLayoutClass(void *);
extern void scrRun(void);
extern SheetSegHeader *GetWorldLayoutSheetSegHeader(void);
extern void *memset(void *, int, unsigned int);
extern void SetInitFogColClassFromStageData(FogInit *data);
extern void SeemlessInitFogTargetParamWorldLayout(void *src);
extern void setLightParam(LightParam *);
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);

void st_stageboundary(void)
{
    StageContext ctx;
    StageContext old;
    void *target;
    unsigned int i;

    while (1) {
        if (D_0017A890 == 0) {
            target = get_cur_camera_target(get_main_cameraman());
            if (GetStageContextByPos(&ctx, iosgluGetCameraContext() + 0x140) != -1 && ctx.id != D_0017A8A0.id) {
                old = D_0017A8A0;
                D_0017A8A0 = ctx;
                if (D_0017A8A0.id != -1) {
                    for (i = 0; i < 2; i++) {
                        if (D_0017A898[i] != 0)
                            D_0017A898[i](&D_0017A8A0, &old);
                    }
                }
            }
            if (target != 0) {
                if (GetStageContextByPos(&ctx, *(void **)(GetLayoutClass(target) + 0x134)) != -1 &&
                    ctx.id != D_0017A8E0.id) {
                    old = D_0017A8E0;
                    D_0017A8E0 = ctx;
                }
            }
        }
        scrRun();
    }
}

static int func_0002D948(char *p)
{
    FogInit copy;
    FogInit fog;
    char *hdr = (char *)GetWorldLayoutSheetSegHeader();
    char *layout;

    if (hdr != 0) {
        layout = *(char **)(hdr + 0x10) + *(int *)(p + 0x20) * 156;
        memset(&fog, 0, sizeof(fog));
        fog.near = *(float *)(layout + 0x20);
        fog.far = *(float *)(layout + 0x24);
        fog.density = *(float *)(layout + 0x28);
        fog.min = *(float *)(layout + 0x2C);
        fog.max = 1.0f;
        fog.r = *(unsigned char *)(layout + 0x30);
        fog.g = *(unsigned char *)(layout + 0x31);
        fog.b = *(unsigned char *)(layout + 0x32);
        fog.a = *(unsigned char *)(layout + 0x33);
        copy = fog;
        SetInitFogColClassFromStageData(&copy);
        SeemlessInitFogTargetParamWorldLayout(layout);
    }
    return 0;
}

static int func_0002DA60(LightRef *r)
{
    SheetSegHeader *h = GetWorldLayoutSheetSegHeader();

    if (h != 0)
        setLightParam(&h->lights[r->light]);
    return 0;
}

void PauseStageBoundaryManager(int pause)
{
    D_0017A890 = pause;
    if (pause == 0) {
        D_0017A8A0 = RO_0017CE40;
        D_0017A8E0 = RO_0017CE40;
    }
}

void *CreateStageBoundaryManager(int arg)
{
    return gcCreateScriptObj(st_stageboundary, 0, rootPtn, 0x2000, 0, arg, RO_0017CE80);
}
