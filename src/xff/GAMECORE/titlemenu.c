typedef struct { int pad0; int *active; int pad8[2]; } SpriteParam;

typedef struct { char pad0[0xC]; float fC; char pad10[0x34]; } SpriteLayer;

typedef struct {
    char pad0[4];
    SpriteLayer *layers;
    char pad8[0x20];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct { char pad[0x170]; float speed; } GcGlobal;

extern void *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern void SpriteMenuSetDispFlagAll(unsigned char *, int);
extern void SpriteMenuSetLayer(unsigned char *o, int layer);
extern int SpriteMenuGetMenuIdByHash(unsigned char *menu, int layer, int name);
extern void SpriteMenuSetDefaultSelectMenu(unsigned char *menu, int layer, int id);
extern int SpriteMenuIsFadeCheckAllLayer(unsigned char *);
extern void scrRun(void);
extern float getFadeValue(void);
extern void *iosMallocAlign(void *, int, int);
extern void iosFree(void *);
extern char rootPtn[];
extern int mcGetInfo(int, int);
extern int mcGetMainDataInfo(int, int, void *);
extern int mcGetLastSaveGameDataIndex(void *);
extern int mcGetGameClearFlag(void);
extern GcGlobal gcGlobalVar;
extern int titleDemoFinishFlag;
extern int D_0017B274;
extern int D_0017B278;
extern int D_0017B27C;
extern int D_0017B280;
extern const char RO_00180A68[];
extern const char RO_00180A78[];
extern const char RO_00180A88[];
extern const char RO_00180A98[];
extern const char RO_00180AA8[];
extern void func_000C95C0(float);

void titlemenu(SpriteParam *parameters)
{
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    void *buf;
    int last;
    int i;
    int r;
    int idx;
    int layer;
    int flags;

    last = -1;
    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    ScrSpriteParamSetup(&local, parameters);
    buf = iosMallocAlign(rootPtn, 0x6C8, 0x10);
    for (i = 0; i < 2; i++) {
        r = mcGetInfo(i, 0);
        if (r == 0 || r == 2) {
            if (mcGetMainDataInfo(i, 0, buf) == 0) {
                idx = mcGetLastSaveGameDataIndex(buf);
                if (idx != -1) {
                    last = idx;
                }
            }
        }
    }
    iosFree(buf);
    if (mcGetGameClearFlag()) {
        layer = SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180A68));
    } else {
        layer = SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180A78));
    }
    D_0017B274 = 1;
    D_0017B278 = 0;
    D_0017B27C = 0;
    D_0017B280 = 1;
    SpriteMenuSetDispFlag(thread, layer, 1);
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180A88)), 1);
    SpriteMenuSetLayer(thread, layer);
    if (last != -1) {
        if (layer == SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180A78))) {
            SpriteMenuSetDefaultSelectMenu(thread, layer,
                SpriteMenuGetMenuIdByHash(thread, MakeStrHashValue(RO_00180A78), MakeStrHashValue(RO_00180A98)));
        } else {
            SpriteMenuSetDefaultSelectMenu(thread, layer,
                SpriteMenuGetMenuIdByHash(thread, MakeStrHashValue(RO_00180A68), MakeStrHashValue(RO_00180AA8)));
        }
    }
    while (*local.active) {
        if (D_0017B280 == 1 && !titleDemoFinishFlag) {
            flags = 9;
        } else {
            flags = 0;
        }
        if (D_0017B278 == 0 && getFadeValue() == 0.0f) {
            menu->exec(thread, gcGlobalVar.speed, flags, 0, 0);
        }
        if (D_0017B27C == 0) {
            func_000C95C0(menu->layers[layer].fC);
            menu->draw(thread);
        }
        scrRun();
    }
    SpriteMenuSetDispFlagAll(thread, 0);
    while (SpriteMenuIsFadeCheckAllLayer(thread)) {
        menu->exec(thread, gcGlobalVar.speed, 0, 0, 0);
        func_000C95C0(menu->layers[layer].fC);
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}
