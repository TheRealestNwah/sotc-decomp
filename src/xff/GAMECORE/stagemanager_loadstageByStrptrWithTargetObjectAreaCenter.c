typedef struct {
    int v[4];
    unsigned short cnt;
    short pad;
} StageData;

extern int *DldSysUndefSymbol;
extern int SH_StageDataDEFAULT[];

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline int stageNum(unsigned int *h)
{
    StageData *p = (StageData *)dldResolve(h);

    if (p != 0) {
        int *sh = DldSysUndefSymbol != SH_StageDataDEFAULT ? SH_StageDataDEFAULT : 0;
        StageData *base = 0;

        if (sh != 0)
            base = (StageData *)sh[4];
        return p - base;
    }
    return -1;
}


extern char gcGlobalVar[];
extern void *D_0017A868;
extern void *D_0017A86C;
extern char *GetLayoutClass(void *);
extern int GetStageContext(void *);
extern void func_0002D570(int);
extern int createScriptObj(void (*)(int), int, int, int, int, int, int, int);
long stagemanager_loadstageByStrptrWithTargetObjectAreaCenter(unsigned int *reference, void *target)
{
    char context[0x40] __attribute__((aligned(16)));
    char *layout = GetLayoutClass(target);
    int stage = stageNum(reference);
    int area;
    *(char **)(context + 4) = layout;
    GetStageContext(context);
    area = D_0017A868 && D_0017A86C ? *(int *)(context + 0x20) : -1;
    return createScriptObj(func_0002D570, (stage << 16) | area,
        *(int *)(gcGlobalVar + 0x308), 0x1000, 0, 1, 0, 0);
}
