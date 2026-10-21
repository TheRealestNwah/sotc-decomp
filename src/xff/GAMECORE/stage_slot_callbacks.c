typedef struct Ptn Ptn;
typedef struct {
    int v[4];
    unsigned short cnt;
    short pad;
} StageData;

extern int *DldSysUndefSymbol;
extern int SH_StageDataDEFAULT[];

static inline StageData *stageData(int n)
{
    int *sh = DldSysUndefSymbol != SH_StageDataDEFAULT ? SH_StageDataDEFAULT : 0;

    return sh != 0 ? (StageData *)sh[4] + n : 0;
}

extern void sheetMgrLoadSegmentIndex(void *, int, int *);
extern void sheetMgrNopSegmentIndex(int);
extern int initstage(Ptn *, int, int, int, int, int);
extern void scrRun(void);

extern Ptn rootPtn;


extern void func_00027B70(int);
extern void func_00026CA8(int);
extern void func_00027418(int);
extern void func_00027070(int);
extern void func_00026E38(int);
extern void func_000272A8(int);
extern void func_00027968(int);
extern void func_00026AB8(int);
extern void *createScriptObj(void (*)(int), int, void *, int, int, int, int, int);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
extern char gcGlobalVar[], B_00188730[];

static void func_0002D458(int handle)
{
    func_00027070(handle);
    func_00026E38(handle);
}
static void func_0002D480(int handle)
{
    void *object;
    func_000272A8(handle);
    object = createScriptObj(func_00026AB8, handle, *(void **)(gcGlobalVar + 0x308),
        0x1000, 0, 1, 0, 0);
    isysAddGroupWithLinkParam(object, B_00188730, 0, 0);
    func_00026E38(handle);
    func_00027968(handle);
}
static void func_0002D4F8(int handle)
{
    void *object;
    func_00027B70(handle);
    func_00027070(handle);
    object = createScriptObj(func_00026CA8, handle, *(void **)(gcGlobalVar + 0x308),
        0x1000, 0, 1, 0, 0);
    isysAddGroupWithLinkParam(object, B_00188730, 0, 0);
    func_00027418(handle);
}
static void func_0002D570(int packed)
{
    int n = packed >> 16;
    int c = packed & 0xFFFF;
    Ptn *a = &rootPtn;
    StageData *s = stageData(n);
    int st;

    if (++s->cnt == 1) {
        sheetMgrLoadSegmentIndex(SH_StageDataDEFAULT, n, &st);
        sheetMgrNopSegmentIndex(0);
        while ((unsigned int)(st - 0xDEAF) >= 2)
            scrRun();
        if (st != 0xDEB0)
            initstage(a, n, c, -1, 1, 0);
    }
}
