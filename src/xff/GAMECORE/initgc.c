typedef struct {
    long a;
    long b;
} TickPair;

typedef struct {
    unsigned long count;
    long tick8;
    TickPair ticks[15];
    char pad100[0x148 - 0x100];
    long tick148;
    char pad150[0x8];
    long tick158;
    long tick160;
    char pad168[0x198 - 0x168];
    int i198;
    float f19C;
    float rate1A0;
    int zero1A4;
    float rate1A8;
    int i1AC;
    long l1B0;
    char pad1B8[0x1C8 - 0x1B8];
    char res1C8[0x228 - 0x1C8];
    int grp228[18];
    int grp270;
    int grp274;
    int grp278;
    int grp27C;
    int grp280;
    int grp284;
    int grp288[8];
    char pad2A8[0x2EC - 0x2A8];
    int grp2EC[4];
    int grp2FC;
    int grp300;
    int grp304;
    void *ptn;
    int i30C;
    int i310;
} GcGlobalVar;

extern GcGlobalVar gcGlobalVar;
extern volatile long gpfinishctr;
extern void isysInitGroup(void *);
extern long iosGetTCountExtension(void);
extern void InitObjectManagerResourceInfo(void *);
extern void func_0000B9C0(void);
extern char rootPtn[];
extern int SH_StageDataDEFAULT[];
extern char D_00179EC8[];
extern char D_00179ED8[];
extern char D_00179EE8[];
extern float D_00179EA4;
extern char D_0000C130[];
extern char D_0000C180[];
extern char D_0000C1D0[];
extern char EntryPadHistory[];
extern void iosInitRandom(float);
extern void gameModeInit(void);
extern void initmanager(void);
extern void sheetMgrCreateStageIndexSkipInfo(int);
extern void usbdevInit(void);
extern void InitPadHistory(void);
extern void initMcManager(void *, void *, void *);
extern void func_0000C0E8(void);
extern void graphInit(void);
extern void optionFlagInit(void);
extern void initScriptSystem(void);
extern void execScript(void);
extern void iosSetISchedulerSubthreadTask(void *);
extern void iosSetIStartFunc(void *);
extern void iosSetIFinishFunc(void *);
extern void iosSetDlTransFunc(void *);
extern void iosSetGpFinishFunc(void *);
extern void iosSetIVSyncMode(int);
extern void iosPadEntryTickFunc(void *);

static void func_0000BBD8(void)
{
    int i;

    for (i = 0; i < 18; i++)
        isysInitGroup(&gcGlobalVar.grp228[i]);
    gcGlobalVar.tick8 = iosGetTCountExtension();
    for (i = 0; i < 15; i++) {
        gcGlobalVar.ticks[i].a = gcGlobalVar.ticks[i].b = gcGlobalVar.tick8;
    }
    gcGlobalVar.f19C = 1.0f;
    gcGlobalVar.rate1A0 = 1.0f;
    gpfinishctr = 0;
    gcGlobalVar.i1AC = 0;
    gcGlobalVar.i198 = 0;
    gcGlobalVar.l1B0 = 0;
    func_0000B9C0();
    gcGlobalVar.i310 = 0;
    gcGlobalVar.i30C = -1;
    isysInitGroup(&gcGlobalVar.grp270);
    isysInitGroup(&gcGlobalVar.grp274);
    isysInitGroup(&gcGlobalVar.grp278);
    isysInitGroup(&gcGlobalVar.grp280);
    isysInitGroup(&gcGlobalVar.grp284);
    isysInitGroup(&gcGlobalVar.grp27C);
    InitObjectManagerResourceInfo(gcGlobalVar.res1C8);
    for (i = 0; i < 8; i++)
        isysInitGroup(&gcGlobalVar.grp288[i]);
    for (i = 0; i < 4; i++)
        isysInitGroup(&gcGlobalVar.grp2EC[i]);
    isysInitGroup(&gcGlobalVar.grp2FC);
    isysInitGroup(&gcGlobalVar.grp300);
    isysInitGroup(&gcGlobalVar.grp304);
}

void initgc(void)
{
    gcGlobalVar.ptn = rootPtn;
    iosInitRandom(9.4356f);
    gameModeInit();
    initmanager();
    sheetMgrCreateStageIndexSkipInfo(SH_StageDataDEFAULT[3]);
    usbdevInit();
    InitPadHistory();
    initMcManager(D_00179EE8, D_00179EC8, D_00179ED8);
    func_0000BBD8();
    gcGlobalVar.rate1A8 = D_00179EA4;
    gcGlobalVar.zero1A4 = 0;
    gcGlobalVar.rate1A0 = D_00179EA4;
    gcGlobalVar.tick160 = gcGlobalVar.tick148 + gcGlobalVar.tick160;
    gcGlobalVar.tick158 = (((gcGlobalVar.count << 8) >> 8) * (int)(D_00179EA4 * 256.0f)) >> 8;
    gcGlobalVar.tick148 = 0;
    graphInit();
    optionFlagInit();
    initScriptSystem();
    iosSetISchedulerSubthreadTask(execScript);
    iosSetIStartFunc(func_0000C0E8);
    iosSetIFinishFunc(D_0000C130);
    iosSetDlTransFunc(D_0000C1D0);
    iosSetGpFinishFunc(D_0000C180);
    iosSetIVSyncMode(0);
    iosPadEntryTickFunc(EntryPadHistory);
}
