typedef struct {
    void (*func)(int);
    int arg;
} SchedSubFunc;

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
static void func_0001B718(void);
static int func_0001B850(int);

static void func_0001B180(void)
{
    int i;
    int cnt;
    int r;
    unsigned long t;

    B_000BF6E0 = 0;
    iosCdSetErrorCallback(ischedStop, ischedRestart);
    iosCreateMsgQueue(B_000BF6E8, 0, 0);
    bootGPThread(func_0001B718);
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
