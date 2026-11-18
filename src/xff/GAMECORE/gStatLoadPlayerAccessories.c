typedef struct Ptn Ptn;
typedef struct {
    int flag;
    int id;
    int pad[2];
} Accessory;

extern Ptn rootPtn;
extern char gcGlobalVar[];
extern Accessory D_0017A200[];
extern Accessory D_0017A250[];
extern int D_0017A284;
extern int D_0017A288;
extern Accessory *D_0017A28C;
extern Accessory *D_0017A290;
extern Accessory B_00188540;
extern char *bossStatGetActiveBoss(void);
extern int _omakeSelectFlagChk(int);
extern void stagemanager_unloadstagecore(int);
extern void stagemanager_loadstagecore(Ptn *, int, int, int);
extern void *SCRGetFirstObj(void *);
extern void nico_hydePlayerByMagireManteau(void *, int);

static inline void changeCore(int old, int id)
{
    if (old != 0) {
        if (id == old)
            return;
        stagemanager_unloadstagecore(old);
    }
    if (id != 0)
        stagemanager_loadstagecore(&rootPtn, id, -1, 0);
}

static inline void setCore(int *slot, int id)
{
    if (id != *slot) {
        if (*slot != 0)
            stagemanager_unloadstagecore(*slot);
        if (id != 0)
            stagemanager_loadstagecore(&rootPtn, id, -1, 0);
        *slot = id;
    }
}

void gStatLoadPlayerAccessories(void)
{
    char *boss = bossStatGetActiveBoss();
    Accessory *a;
    Accessory *b;
    Accessory *sel;
    int id;

    for (a = D_0017A200; a->flag != 0; a++) {
        if (_omakeSelectFlagChk(a->flag))
            break;
    }
    for (b = D_0017A250; b->flag != 0; b++) {
        if (_omakeSelectFlagChk(b->flag)) {
            sel = b;
            goto found;
        }
    }
    if (boss != 0)
        b->id = *(int *)(boss + 0xB0);
    else
        b->id = 0xB9;
    sel = b;
found:
    changeCore(D_0017A28C->id, a->id);
    D_0017A28C = a;
    changeCore(D_0017A290 != 0 ? D_0017A290->id : 0, b->id);
    B_00188540 = *sel;
    D_0017A290 = &B_00188540;
    setCore(&D_0017A284, boss != 0 ? *(int *)(boss + 0xA8) : 0xB8);
    setCore(&D_0017A288, boss != 0 ? *(int *)(boss + 0xAC) : 0xB7);
    nico_hydePlayerByMagireManteau(SCRGetFirstObj(gcGlobalVar + 0x2B0), _omakeSelectFlagChk(7) != 0);
}
