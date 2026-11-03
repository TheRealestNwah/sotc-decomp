extern int DldSysUndefSymbol;
extern char *GetScriptLayoutClass(void *);
extern int stagemanager_getStageNumberWithStageDataStrptr(char *);
extern void sheetMgrLoadSegmentIndex(void *, int, int *);
extern void scrRun(void);
extern char SH_StageDataDEFAULT[];
extern float func_000D3D60(char *, void *);

typedef struct {
    char pad0[0x14];
    char *layout;
    char *stage;
    char *data;
    int stageNo;
    int unk24;
    float unk28;
    char pad2C[0x14];
    float unk40;
    char pad44[0xC];
    char unk50[1];
} Work;

static inline char *DldGetPtr(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static void func_000D3F00(Work *w, void *arg)
{
    int st;
    int no;
    float f;

    w->layout = GetScriptLayoutClass(arg);
    w->stage = DldGetPtr((unsigned int *)*(char **)(w->layout + 0x2DC));
    no = stagemanager_getStageNumberWithStageDataStrptr(w->stage + 0xC);
    sheetMgrLoadSegmentIndex(SH_StageDataDEFAULT, no, &st);
    while ((unsigned int)(st - 0xDEAF) >= 2)
        scrRun();
    w->stageNo = no;
    w->data = DldGetPtr((unsigned int *)(w->stage + 8));
    f = func_000D3D60(w->data, w->unk50);
    w->unk24 = 0;
    w->unk28 = f;
    w->unk40 = f;
}
