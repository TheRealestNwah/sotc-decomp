/* Parked attempt: 151 diffs (try_compilers -O2 -G0). The mouse polling thread; the
   shape and size match, register allocation of the hoisted %hi parts does not. */
#ifdef NONMATCHING
extern int B_000C4A60;
extern char B_000C4A00[];
extern int B_000C4A40;
extern int D_00040FC4;
typedef struct {
    int port;
    int pad;
    int b[4];
} MouseEvent;
extern void (*D_00040FC8)(MouseEvent);
extern void func_0001F338();
extern void WaitSema(int);
extern void SignalSema(int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern void waitVscheduler(void);

static inline int msInfo(void *rbuf)
{
    int ret = 0;

    if (D_00040FC4) {
        WaitSema(B_000C4A60);
        ret = sceSifCallRpc(B_000C4A00, 1, 1, &B_000C4A40, 0x20, rbuf, 0x20, func_0001F338, 0);
    }
    return ret;
}

static inline int msCall(int fn, int arg, void *rbuf)
{
    int ret = 0;

    if (D_00040FC4) {
        WaitSema(B_000C4A60);
        B_000C4A40 = arg;
        ret = sceSifCallRpc(B_000C4A00, fn, 1, &B_000C4A40, 0x20, rbuf, 0x20, func_0001F338, 0);
    }
    return ret;
}

static inline void msSync(void)
{
    if (D_00040FC4) {
        WaitSema(B_000C4A60);
        SignalSema(B_000C4A60);
    }
}

static void func_0001F070(void)
{
    unsigned char info[0x80];
    unsigned char st[0x80];
    signed char ev[0x80];
    int i;

top:
    while (msInfo(info) != 0) {
    }
    msSync();
    for (i = 0; i < info[0]; i++) {
        if (info[2 + i] == 0) {
            continue;
        }
        if (msCall(3, 0, st) != 0) {
            continue;
        }
        msSync();
        while (msCall(2, i, ev) == 0) {
            msSync();
            if (ev[0] == 0) {
                break;
            }
            if (D_00040FC8) {
                MouseEvent e = {i, 0, {ev[1], ev[2], ev[3], ev[4]}};
                D_00040FC8(e);
            }
        }
    }
    waitVscheduler();
    goto top;
}
#endif
