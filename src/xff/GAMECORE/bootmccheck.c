typedef struct { char c[8]; int *result; char pad[4]; } SpriteParam;

typedef struct {
    char pad0[0x8];
    int count;
    char padC[0x4];
    int flags;
    char pad14[0x14];
    void (*exec)(unsigned char *, float, int, int, int);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct { char pad[0x170]; float speed; } GcGlobal;

extern int D_0017A97C;
extern int D_0017A980;
extern int D_0017A984;
extern int D_0017A98C;
extern unsigned char *D_0017A990;
extern SpriteMenu *D_0017A994;
extern int B_0018A4D8;
extern int B_0018A4DC;
extern int mcMainNeedCluster;
extern GcGlobal gcGlobalVar;
extern unsigned char *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, void *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern void SpriteMenuSetPartsDefValueByHashStr(unsigned char *, const char *, const char *, int);
extern void SpriteMenuSetNumPartsFormatByHashStr(unsigned char *, const char *, const char *, int);
extern void SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(unsigned char *, const char *, const char *, int);
extern void SpriteMenuSetDispFlag(unsigned char *, int, int);
extern void SpriteMenuSetLayer(unsigned char *, int);
extern int SpriteMenuIsFadeCheckLayer(unsigned char *, int);
extern int SpriteMenuGetSelectMenuIdBySpriteMenuClass(SpriteMenu *);
extern void scrRun(void);

static const char RO_0017D030[] = "MEMOCA_NOT_ENOUGH";
static const char RO_0017D048[] = "SAVE_MEMOCASLOT_NUMBER";
static const char RO_0017D060[] = "MEMOCA_NOTHING";
static const char RO_0017D070[] = "BOOT_FILESIZE";
static const char RO_0017D080[] = "MEMOCA_LOAD_ALERT";

static inline void dispLayer(unsigned char *th, int layer)
{
    SpriteMenu *m = GetSpriteMenuClass(th);
    int i;

    for (i = 0; i < m->count; i++)
        SpriteMenuSetDispFlag(th, i, i == layer);
}

void bootmccheck(void *arg)
{
    SpriteParam param;
    unsigned char *th;
    SpriteMenu *menu;
    int loop;
    int slot;

    loop = 1;
    th = isysGetThisSubThread();
    menu = GetSpriteMenuClass(th);
    ScrSpriteParamSetup(&param, arg);
    D_0017A990 = th;
    D_0017A994 = menu;
    D_0017A98C = -1;
    D_0017A984 = 1;
    SpriteMenuSetPartsDefValueByHashStr(th, RO_0017D060, RO_0017D070, mcMainNeedCluster);
    SpriteMenuSetNumPartsFormatByHashStr(th, RO_0017D060, RO_0017D070, 3);
    SpriteMenuSetPartsDefValueByHashStr(th, RO_0017D030, RO_0017D070, mcMainNeedCluster);
    SpriteMenuSetNumPartsFormatByHashStr(th, RO_0017D030, RO_0017D070, 3);
    do {
        slot = D_0017A980;
        if (slot != -1) {
            SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(th, RO_0017D030, RO_0017D048, slot);
            SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(th, RO_0017D060, RO_0017D048, slot);
        }
        switch (D_0017A97C) {
        case 0:
            dispLayer(th, -1);
            break;
        case 1:
            if (!SpriteMenuIsFadeCheckLayer(th, 0))
                loop = 0;
            break;
        case 2:
            dispLayer(th, 0);
            SpriteMenuSetLayer(th, 0);
            if (menu->flags & 1) {
                switch (SpriteMenuGetSelectMenuIdBySpriteMenuClass(menu)) {
                case 0:
                    dispLayer(th, -1);
                    D_0017A97C = 0;
                    break;
                case 1:
                    dispLayer(th, -1);
                    loop = 0;
                    break;
                }
            }
            menu->flags = 0;
            break;
        case 3:
            dispLayer(th, 1);
            SpriteMenuSetLayer(th, 1);
            if (menu->flags & 1) {
                switch (SpriteMenuGetSelectMenuIdBySpriteMenuClass(menu)) {
                case 0:
                    dispLayer(th, -1);
                    D_0017A97C = 0;
                    break;
                case 1:
                    dispLayer(th, -1);
                    loop = 0;
                    break;
                }
            }
            menu->flags = 0;
            break;
        case 4:
            dispLayer(th, 2);
            SpriteMenuSetLayer(th, 2);
            SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(th, RO_0017D080, RO_0017D048, B_0018A4DC);
            break;
        }
        menu->exec(th, gcGlobalVar.speed, 1, 0, 0);
        menu->draw(th);
        scrRun();
    } while (loop);
    *param.result = D_0017A98C;
    ScrSpriteParamEnd(&param, 1);
    B_0018A4D8 = 0;
    D_0017A984 = 0;
}
