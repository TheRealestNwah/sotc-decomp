typedef struct { char c[16]; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct {
    int pad0;
    int state;
    int busy;
    int flags;
    int pad10[2];
    int unk18;
} TimeAttack;

typedef struct { char pad[0x170]; float speed; } GcGlobal;

extern void *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern TimeAttack g_TimeAttack;
extern const char RO_00180838[];

static inline int timeAttackOverBGCheck(unsigned char *thread, TimeAttack *rp)
{
    switch (rp->state) {
    case 8:
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180838)), 0);
        return 1;
    case 11:
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180838)), 0);
        return 1;
    }
    if (rp->flags & 0x80) {
        rp->flags &= ~0x80;
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180838)), 0);
        return 1;
    }
    return 0;
}

void timeAttackOverBGScript(SpriteParam *parameters)
{
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    TimeAttack *rp;
    int saved;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    rp = &g_TimeAttack;
    saved = rp->busy;
    ScrSpriteParamSetup(&local, parameters);
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180838)), 1);
    while (1) {
        rp->busy = 1;
        menu->exec(thread, gcGlobalVar.speed, 1, 0, rp);
        if (timeAttackOverBGCheck(thread, rp)) {
            break;
        }
        menu->draw(thread);
        scrRun();
    }
    rp->busy = saved;
    ScrSpriteParamEnd(&local, 1);
}
