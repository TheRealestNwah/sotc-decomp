/* Parked attempt: 120 diffs (try_compilers -O2 -G0). The keyboard polling thread; the
   shape and size match, register allocation of the hoisted %hi parts does not. */
#ifdef NONMATCHING
extern int B_000C3980;
extern char B_000C3988[];
extern int B_000C39C0;
extern int D_00040FBC;
extern void (*D_00040FC0)(void *);
extern void func_0001EFE8();
extern void WaitSema(int);
extern void SignalSema(int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern void waitVscheduler(void);

static inline int kbCall(int fn, int arg, void *rbuf)
{
    int ret = 0;

    if (D_00040FBC) {
        WaitSema(B_000C3980);
        B_000C39C0 = arg;
        ret = sceSifCallRpc(B_000C3988, fn, 1, &B_000C39C0, 0x20, rbuf, 0x20, func_0001EFE8, 0);
    }
    return ret;
}

static inline void kbSync(void)
{
    if (D_00040FBC) {
        WaitSema(B_000C3980);
        SignalSema(B_000C3980);
    }
}

static inline int kbInfo(void *buf)
{
    WaitSema(B_000C3980);
    return sceSifCallRpc(B_000C3988, 1, 1, &B_000C39C0, 0x20, buf, 0x20, func_0001EFE8, 0);
}

static void func_0001ED70(void)
{
    unsigned char info[0x80];
    unsigned char st[0x80];
    signed char ev[0x80];
    int i;

top:
    {
retry:
        if (kbInfo(info) != 0)
            goto retry;
        kbSync();
        for (i = 0; i < info[0]; i++) {
            if (info[2 + i] == 0) {
                continue;
            }
            if (kbCall(3, 0, st) != 0) {
                continue;
            }
            kbSync();
            while (kbCall(2, i, ev) == 0) {
                kbSync();
                if (ev[1] == 0) {
                    break;
                }
                if (D_00040FC0) {
                    D_00040FC0(ev);
                }
            }
        }
        waitVscheduler();
    }
    goto top;
}
#endif
