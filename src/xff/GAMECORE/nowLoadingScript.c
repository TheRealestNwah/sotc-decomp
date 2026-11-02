typedef struct {
    char pad0[0x168];
    float f168;
    char pad16C[0x170 - 0x16C];
    float f170;
} GcGlobalVar;

typedef struct {
    char pad0[0x28];
    void (*draw)(void *, int, int, int, float);
    void (*flush)(void *);
} SpriteMenu;

extern GcGlobalVar gcGlobalVar;
extern int D_0017ABCC;
extern void *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(void *);
extern void *texSearchMopByName(char *);
extern void SpriteMenuSetLayer(void *, int);
extern void SpriteMenuSetDispFlagAll(void *, int);
extern int SpriteMenuIsFadeCheckAllLayer(void *);
extern float texAnimationOne(void *, float, float);
extern void scrRun(void);

void nowLoadingScript(void)
{

    void *th = isysGetThisSubThread();
    SpriteMenu *sm = GetSpriteMenuClass(th);
    void *mop = texSearchMopByName("loading");
    float t;
    int prev;

    t = gcGlobalVar.f168;
    D_0017ABCC = 0;
    prev = -1;
    SpriteMenuSetLayer(th, 0);
    for (;;) {
        if (prev != D_0017ABCC)
            SpriteMenuSetDispFlagAll(th, D_0017ABCC);
        if (D_0017ABCC != 0 || SpriteMenuIsFadeCheckAllLayer(th))
            t = texAnimationOne(mop, t, gcGlobalVar.f170);
        sm->draw(th, 0, 0, 0, gcGlobalVar.f170);
        sm->flush(th);
        prev = D_0017ABCC;
        scrRun();
    }
}
