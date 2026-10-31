extern int B_000C0710[];
extern long B_000BF6D0;
extern volatile int B_000BF6E0;
extern volatile int D_00040D64;
extern volatile int vschedGameTime;
extern int vschedGameTimeExec;
extern void (*schedAdpcmTickProc)(void);
extern void iosCreateMsgQueue(void *, void *, int);
extern int iosRecvMsg(void *, int *, int);
extern void iosSleepThread(void);
extern long iosGetTCountExtension(void);
extern void tickProcSound(int);
extern void iosPadTickProc(void);

static void T_0001B740(void)
{
    iosCreateMsgQueue(B_000C0710, 0, 0);
    for (;;) {
        iosSleepThread();
        B_000BF6D0 = iosGetTCountExtension();
        if (B_000BF6E0 == 0) {
            D_00040D64++;
        }
        if (vschedGameTimeExec != 0) {
            vschedGameTime++;
        }
        tickProcSound(B_000BF6E0);
        if (schedAdpcmTickProc != 0) {
            schedAdpcmTickProc();
        }
        iosPadTickProc();
        iosRecvMsg(B_000C0710, 0, 0);
    }
}
