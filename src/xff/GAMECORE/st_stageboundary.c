typedef struct {
    long a[4];
    int id;
    int pad;
    long b[3];
} StageContext;

typedef void (*BoundaryCB)(StageContext *, StageContext *);

extern int D_0017A890;
extern BoundaryCB D_0017A898[2];
extern StageContext D_0017A8A0;
extern StageContext D_0017A8E0;
extern void *get_main_cameraman(void);
extern void *get_cur_camera_target(void *);
extern char *iosgluGetCameraContext(void);
extern int GetStageContextByPos(StageContext *, void *);
extern char *GetLayoutClass(void *);
extern void scrRun(void);

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
