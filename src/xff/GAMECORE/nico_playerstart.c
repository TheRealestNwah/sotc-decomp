extern int *DldSysUndefSymbol;


static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

extern char rootPtn[];
extern char *WeaponList_SWORD;
extern char YUnitVector[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern char *GetCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern void SetLayoutObjDebugResetFunc(void *, void (*)(void));
extern void SetLayoutObjSubDispFunc(void *, void (*)(void), int);
extern void MVHIST_Init(void *);
extern void player_initHangPointWork(void *);
extern void player_initAvoidDangerCliffWork(void *, void *);
extern void player_initSlipEffect(void *, void *);
extern void SetCollisionEdgeLinkDBFinderCollectStatus(int, int, int, void *, void (*)(void), float);
extern void func_0007C0D0(void);
extern void func_0007C700(void);
extern void func_0007C828(void);
extern void nico_player1(void);

void nico_playerstart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x1CC3);
    char *c;
    char *w;
    char *wp;
    char *cc;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x1C90, 0x10);
    *(char **)(c + 0x1200) = w;
    wp = WeaponList_SWORD;
    *(char **)(GetCharacterClass(th) + 0x111C) = dldResolve((unsigned int *)(wp + 0x14));
    *(char **)(GetCharacterClass(th) + 0x1120) = dldResolve((unsigned int *)(wp + 0x18));
    SetLayoutObjDebugResetFunc(th, func_0007C0D0);
    SetLayoutObjSubDispFunc(th, func_0007C700, 0);
    *(int *)(w + 0xD98) = 0;
    MVHIST_Init(w + 0xE00);
    *(char **)w = dldResolve(*(unsigned int **)(GetCharacterClass(th) + 0x3F4));
    player_initHangPointWork(w + 0x1AC0);
    player_initAvoidDangerCliffWork(th, w + 0x1BB0);
    player_initSlipEffect(th, w + 0x1C68);
    cc = GetCharacterClass(th);
    SetCollisionEdgeLinkDBFinderCollectStatus(*(int *)(cc + 0xE40), 0, 1, YUnitVector, func_0007C828, 1.0f);
    cc[0xB10] = 1;
    cc[0xB11] = 1;
    *(int *)(w + 0x1C60) = 0;
    isysJumpSubThread(nico_player1, w);
}
