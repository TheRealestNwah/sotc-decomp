typedef struct { void *buf; int n; char pad[0x14]; } MsgQueue;
typedef struct {
    unsigned char stat, second, minute, hour, pad, day, month, year;
} sceCdCLOCK;
typedef union { sceCdCLOCK clock; long raw; } ClockValue;
struct tm { int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst; };

extern MsgQueue B_0004E5B0;
extern char B_0004E5D0[];
extern int *B_0004F5D0;
extern long B_0004F5D8;
extern int D_00040598;
extern void iosCreateMsgQueue(MsgQueue *, void *, int);
extern int *iosCreateThread(void *, void *, int, int, int);
extern int iosStartThread(int *, void *);
extern int iosRecvMsg(MsgQueue *, int *, int);
extern int sceCdReadClock(sceCdCLOCK *);
extern long mktime(struct tm *);

static void func_00000910(void);

int iosCreateIdleThread(void)
{
    iosCreateMsgQueue(&B_0004E5B0, 0, 0);
    B_0004F5D0 = iosCreateThread(func_00000910, B_0004E5D0, 0x1000, 0x7D, 0);
    return iosStartThread(B_0004F5D0, 0);
}

void iosGetClock(long *arg0)
{
    *arg0 = B_0004F5D8;
}

long iosGetClockSecond(unsigned char *c)
{
    struct tm t;
    if (c[0] != 0)
        return 0;
    t.tm_sec = c[1];
    t.tm_min = c[2];
    t.tm_hour = c[3];
    t.tm_mday = c[5];
    t.tm_mon = c[6] - 1;
    t.tm_year = c[7] - 1900;
    t.tm_wday = 0;
    t.tm_yday = 0;
    t.tm_isdst = 0;
    return mktime(&t);
}

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
