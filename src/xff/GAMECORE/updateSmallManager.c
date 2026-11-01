typedef struct {
    char a[0x9E0];
    char b[0x13C0 - 0x9E0];
    int f13C0;
    int f13C4;
    int f13C8;
    int f13CC;
    int f13D0;
} SmallMgr;
extern SmallMgr B_0019B870;
extern void terminateSmallManager(void);
extern void func_000B53E0(void *, int, int);
extern void func_000B5548(void *, void *);
extern void func_000B7388(void *, int);
extern void *GetLayoutClass(void *);
extern int _gameWorkChk(int);
extern void _gameWorkSet(int, int);
extern void iosGetClock(void *);
extern long iosGetClockSecond(void *);
extern double difftime(long, long);
extern void tailsFlagsAllClr(void);
extern unsigned int iosGetMallocRootPtnRemainSize(void);

void updateSmallManager(void *obj)
{
    void *layout;
    long now;
    long t;
    int hi, lo;
    char clk[16];

    if (obj == 0) {
        if (B_0019B870.f13CC != 0) {
            terminateSmallManager();
            func_000B53E0(B_0019B870.a, 10, 0);
            func_000B53E0(B_0019B870.b, 20, 1);
            B_0019B870.f13CC = 0;
            B_0019B870.f13D0 = 1;
        }
        return;
    }
    layout = GetLayoutClass(obj);
    B_0019B870.f13CC = 1;
    B_0019B870.f13C0 = 0;
    B_0019B870.f13C4 = 0;
    B_0019B870.f13C8 = 0;
    hi = _gameWorkChk(9);
    lo = _gameWorkChk(10);
    iosGetClock(clk);
    now = iosGetClockSecond(clk);
    t = ((unsigned long)hi << 32) | (unsigned int)lo;
    if (now != 0 && t != 0 && difftime(t, now) > 86400.0) {
        tailsFlagsAllClr();
        _gameWorkSet(9, 0);
        _gameWorkSet(10, 0);
    }
    func_000B5548(B_0019B870.a, layout);
    func_000B5548(B_0019B870.b, layout);
    if (iosGetMallocRootPtnRemainSize() < 0x100000) {
        func_000B7388(B_0019B870.b, 0);
        func_000B7388(B_0019B870.a, 0);
        func_000B7388(B_0019B870.b, 1);
        func_000B7388(B_0019B870.a, 1);
    }
}
