typedef struct { void *buf; int n; char pad[0x14]; } MsgQueue;
extern MsgQueue B_0004E5B0;
extern char B_0004E5D0[];
extern int *B_0004F5D0;
static void func_00000910(void);
extern void iosCreateMsgQueue(MsgQueue *, void *, int);
extern int *iosCreateThread(void *, void *, int, int, int);
extern int iosStartThread(int *, void *);

int iosCreateIdleThread(void)
{
    iosCreateMsgQueue(&B_0004E5B0, 0, 0);
    B_0004F5D0 = iosCreateThread(func_00000910, B_0004E5D0, 0x1000, 0x7D, 0);
    return iosStartThread(B_0004F5D0, 0);
}

typedef struct {
    unsigned char stat, second, minute, hour, pad, day, month, year;
} sceCdCLOCK;
typedef union { sceCdCLOCK clock; long raw; } ClockValue;
extern int sceCdReadClock(sceCdCLOCK *);
extern int iosRecvMsg(MsgQueue *, int *, int);
extern int D_00040598;
extern long B_0004F5D8;
static void func_00000910(void)
{
    ClockValue value;
    for (;;) {
        iosRecvMsg(&B_0004E5B0, 0, 0);
        if (--D_00040598 >= 0)
            continue;
        if (sceCdReadClock(&value.clock) == 1 && value.clock.stat == 0)
            B_0004F5D8 = value.raw;
        D_00040598 = 1000000;
    }
}
