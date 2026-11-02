typedef struct {
    int pad0;
    int easy;
    int hard;
    int pad0C[3];
    int sel;
    int pad1C;
} OmakeEntry;

typedef struct {
    char pad0[0xC];
    int count;
    OmakeEntry *entries;
} OmakeMenu;

extern char g_Replay[];
extern int *DldSysUndefSymbol;
extern int SH_ItemMenuDEFAULT[];
extern const char RO_00180910[];
extern int D_0017B25C;
extern int ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_PAUSE;
extern int getGameHardMode(void);
extern int MakeStrHashValue(const char *);
extern int _omakeGetFlagChk(int);
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

void ReplayPauseScriptBegin(void)
{
    char *r = g_Replay;
    int cnt;
    OmakeMenu *m;
    int n;
    int count;
    OmakeEntry *e;

    cnt = 0;
    *(int *)(r + 0x4) = 2;
    *(int *)(r + 0x8) = 0;
    *(int *)(r + 0xC) &= ~4;
    m = DldSysUndefSymbol == SH_ItemMenuDEFAULT ? 0 : (OmakeMenu *)SH_ItemMenuDEFAULT;
    count = m->count;
    e = m->entries;
    for (n = 0; n < count; n++) {
        int hash;
        if (getGameHardMode())
            hash = e[n].hard;
        else
            hash = e[n].easy;
        if (hash != MakeStrHashValue(RO_00180910)) {
            if (_omakeGetFlagChk(e[n].sel))
                cnt++;
        }
    }
    count = cnt != 0;
    *(int *)(r + 0x1C) = count;
    if (D_0017B25C != 0) {
        D_0017B25C = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_PAUSE, 0, 0, &D_0017B25C, 0, 0);
    }
}
