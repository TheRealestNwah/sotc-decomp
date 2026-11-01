typedef struct { int a; int *run; int mode; int c; } SpriteParam;

typedef struct { char pad[0x168]; float time; int pad2; float dt; } GV;
extern GV gcGlobalVar;
extern int D_0017A998;
extern void *isysGetThisSubThread(void);
extern char *GetSpriteMenuClass(void *);
extern void ScrSpriteParamSetup(SpriteParam *, void *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern int MakeStrHashValue(const char *);
extern int SpriteMenuGetLayerNoByHash(void *, int);
extern void SpriteMenuSetLayer(void *, int);
extern void SpriteMenuSetDispFlag(void *, int, int);
extern int SpriteMenuIsFadeCheckLayer(void *, int);
extern void scrRun(void);

void bootscelogo(void *arg)
{
    SpriteParam p;
    void *t = isysGetThisSubThread();
    char *m = GetSpriteMenuClass(t);
    float start = 0.0f;
    int cont = 1;
    int layer;

    ScrSpriteParamSetup(&p, arg);
    layer = SpriteMenuGetLayerNoByHash(t, MakeStrHashValue("SCEI_LOGO"));
    SpriteMenuSetLayer(t, 0);
    D_0017A998 = 0;
    do {
        switch (D_0017A998) {
        case 0:
            SpriteMenuSetDispFlag(t, layer, 1);
            D_0017A998 = 1;
            break;
        case 1:
            if (!SpriteMenuIsFadeCheckLayer(t, layer)) {
                D_0017A998 = 2;
                start = gcGlobalVar.time;
            }
            break;
        case 2:
            if (*p.run == 0 && gcGlobalVar.time - start > 3.0f) {
                SpriteMenuSetDispFlag(t, layer, 0);
                D_0017A998 = 3;
            }
            break;
        case 3:
            if (!SpriteMenuIsFadeCheckLayer(t, layer)) {
                D_0017A998 = 4;
            }
            break;
        case 4:
            D_0017A998 = 0;
            cont = 0;
            break;
        }
        (*(void (**)(void *, int, int, int, float))(m + 0x28))(t, 1, 0, 0, gcGlobalVar.dt);
        (*(void (**)(void *))(m + 0x2C))(t);
        scrRun();
    } while (cont);
    ScrSpriteParamEnd(&p, 1);
}
