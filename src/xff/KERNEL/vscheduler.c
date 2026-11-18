typedef struct {
    void (*func)(int);
    int arg;
} SchedSubFunc;
typedef struct { int start; float ofs; } VTime;
typedef struct Thread {
    char pad[0x28];
    struct Thread *next;
} Thread;
typedef struct {
    int msg;
    int unk4;
} MsgEntry;
typedef struct {
    MsgEntry *buf;
    int size;
    int count;
    int wr;
    int unk10;
    int recv;
    Thread *send;
} MsgQueue;
typedef struct { void *func; int arg; } ITask;

extern int D_00040D60;
extern int D_00040D5C;
extern int B_000BF6CC;
extern void SignalSema(int);
extern volatile int B_000BF6E0;
extern char B_000BF6E8[];
extern SchedSubFunc B_000C0730[3];
extern long B_000BF6D8;
extern unsigned long B_000BF6D0;
extern int D_00040D88;
extern int D_00040D6C;
extern int D_00040D70;
extern int D_00040D78;
extern volatile int D_00040D64;
extern void (*D_00040D84)(void);
extern void (*schedAdpcmFunc)(int);
extern int schedGarbageDisableFlag;
extern int ischedExecSubThread;
extern int gpMainCallCounter;
extern char rootPtn[];
extern void ischedStop(void);
extern void ischedRestart(void);
extern void iosCdSetErrorCallback(void (*)(void), void (*)(void));
extern void iosCreateMsgQueue(void *, void *, int);
extern void bootGPThread(void (*)(void));
extern void *memset(void *, int, unsigned int);
extern void init_letter_manager(char *, int);
extern void isysDeleteObjManager(int);
extern void iStart(void);
extern void iFinish(void);
extern void sndSepTickProc(void);
extern void doit_letter_manager(void);
extern int iosChkGpDlTransExec(void);
extern unsigned long iosGetTCountExtension(void);
extern void iosMallocGarbageTickProc(int (*)(int), int);
extern void iosWaitIdleThread(void);
extern int iosSendMsg(void *, int, int);
extern int getIntrGpCount(void);
extern void iosGPFrameInit(void);
static int func_0001B718(void);
extern int iosRecvMsg(void *, int, int);
static int func_0001B850(int);
extern char B_000C0710[];
extern void iosPadInit(void);
extern void iosCreateIVArbitrationSema(void);
extern int *iosCreateThread(void *, void *, int, int, int);
extern int iosStartThread(int *, void *);
extern int iosAddIntcHandler(int, void *);
extern char D_0001B740[], D_0001B820[];
static void func_0001B180(void);
extern char B_000BF710[], B_000C0750[];
extern int *B_000BF704, *B_000C0748;

void isysObjSignalSema(void)
{
    int *p = &D_00040D60;
    if (--*p == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}

static void func_0001B180(void)
{
    int i;
    int cnt;
    int r;
    unsigned long t;

    B_000BF6E0 = 0;
    iosCdSetErrorCallback(ischedStop, ischedRestart);
    iosCreateMsgQueue(B_000BF6E8, 0, 0);
    bootGPThread((void (*)(void))func_0001B718);
    memset(B_000C0730, 0, sizeof(B_000C0730));
    init_letter_manager(rootPtn, 0x4CCCC);
    for (;;) {
        isysDeleteObjManager(gpMainCallCounter);
        gpMainCallCounter = 0;
        iStart();
        if (D_00040D84 != 0) {
            ischedExecSubThread = 1;
            D_00040D84();
            ischedExecSubThread = 0;
        }
        sndSepTickProc();
        if (schedAdpcmFunc != 0) {
            schedAdpcmFunc(0);
        }
        for (i = 0; i < 3; i++) {
            if (B_000C0730[i].func != 0) {
                B_000C0730[i].func(B_000C0730[i].arg);
            }
        }
        D_00040D78++;
        while (B_000BF6E0 != 0) {
        }
        doit_letter_manager();
        B_000BF6D8 = 0;
        if (D_00040D88 == 0 && schedGarbageDisableFlag == 0) {
            cnt = D_00040D64;
            while (iosChkGpDlTransExec() != 0) {
            }
            if (D_00040D6C == 0) {
                r = 0;
                if (cnt == D_00040D64 && (float)(iosGetTCountExtension() - B_000BF6D0) < 2124999.75f)
                    r = 1;
            } else {
                r = 1;
            }
            if (r) {
                t = iosGetTCountExtension();
                iosMallocGarbageTickProc(func_0001B850, cnt);
                D_00040D6C = 0;
                B_000BF6D8 = iosGetTCountExtension() - t;
            }
            iFinish();
        } else {
            iFinish();
            D_00040D88 = 0;
        }
        if (D_00040D70 != 0) {
            iosWaitIdleThread();
        } else {
            iosSendMsg(B_000BF6E8, 0, 1);
            getIntrGpCount();
            iosGPFrameInit();
        }
    }
}

int getVIntrCnt(void)
{
    return D_00040D64;
}

void setVIntrBaseTime(VTime *time)
{
    time->start = D_00040D64;
    time->ofs = 0.0f;
}

float getVIntrDiffTime(VTime *t)
{
    float f = D_00040D64 - t->start;
    int n = f * 0.01668335f;
    return (float)n + (f - (float)n * 59.94f) * 0.01668335f + t->ofs;
}

void addVIntrTime(VTime *t, float dt)
{
    float f = D_00040D64 - t->start;
    int n = f * 0.01668335f;
    float sec = (float)n + (f - (float)n * 59.94f) * 0.01668335f;
    t->ofs = dt - sec;
}

void waitVscheduler(void)
{
    iosSendMsg((MsgQueue *)B_000C0710, 0, 1);
}

void bootSchedulerThread(void)
{
    iosPadInit();
    D_00040D70 = 0;
    iosCreateIVArbitrationSema();
    B_000BF704 = iosCreateThread(D_0001B740, B_000BF710, 0x1000, 0x28, 0);
    iosStartThread(B_000BF704, 0);
    iosAddIntcHandler(2, D_0001B820);
    B_000C0748 = iosCreateThread(func_0001B180, B_000C0750, 0x2000, 0x2D, 0);
    iosStartThread(B_000C0748, 0);
}

void iosAddISchedulerTaskList(void *func, int arg)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (B_000C0730[i].func == 0) {
            B_000C0730[i].func = (void (*)(int))func;
            B_000C0730[i].arg = arg;
            return;
        }
    }
    __asm__ __volatile__("break 0");
}

int iosGetISchedulerExecCnt(void)
{
    return D_00040D78;
}

void ischedStop(void)
{
    if (B_000BF6E0 == 0)
        *(volatile int *)0x10000010 &= ~0x80;
    B_000BF6E0++;
}

void ischedRestart(void)
{
    B_000BF6E0--;
    if (B_000BF6E0 == 0)
        *(volatile int *)0x10000010 |= 0x80;
}

void iosSetISchedulerSubthreadTask(void (*arg0)(void))
{
    D_00040D84 = arg0;
}

void iosSetIVSyncMode(int arg0)
{
    D_00040D70 = arg0;
}

int iosGetIVSyncMode(void)
{
    return D_00040D70;
}

void vschedSetNextFrameForceGarbage(void)
{
    D_00040D6C = 1;
}

long GetGarbageTime(void)
{
    return B_000BF6D8;
}

static int func_0001B718(void)
{
    return iosRecvMsg(B_000BF6E8, 0, 0);
}

static int func_0001B850(int cnt)
{
    int r;

    if (D_00040D6C == 0) {
        r = 0;
        if (cnt == D_00040D64 && (float)(iosGetTCountExtension() - B_000BF6D0) < 2124999.75f)
            r = 1;
    } else {
        r = 1;
    }
    return r;
}
