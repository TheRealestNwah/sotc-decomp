extern int *DldSysUndefSymbol;
extern unsigned int *SeamlessCommonLayout_player;
extern char rootPtn[];
extern int stagemanager_getStageNumberWithStageDataStrptr(void *);
extern void stagemanager_loadstagecore(void *, int, int, int);
extern void stagemanager_unloadstagecore(int);
extern void _gameWorkSet(int, int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

static void func_000128E0(int level)
{
    unsigned int *layout = SeamlessCommonLayout_player;
    int stage;

    stage = stagemanager_getStageNumberWithStageDataStrptr((int *)dldResolve(layout) + level);
    stagemanager_loadstagecore(rootPtn, stage, 0x2D, 1);
    stagemanager_unloadstagecore(layout[1]);
    layout[1] = stage;
    _gameWorkSet(7, level);
}
