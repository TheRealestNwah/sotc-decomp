typedef struct Sheet {
    char pad0[0x44];
    unsigned int flags;
    char pad48[4];
    struct Sheet *loadNext;
    struct Sheet *initNext;
} Sheet;

extern void func_000E47A0(Sheet *);
extern void func_000E2358(Sheet *);
extern void sheetMgrResolve(int);
extern void iosSleepThread(void);
extern void isysRequestDeleteObj(void *);
extern Sheet *B_00151848;
extern Sheet *B_00151850;
extern int D_00139F1C;
extern int D_00139F20;

static void func_000E26D8(void)
{
    Sheet *s;
    Sheet *c;
    Sheet *n;
    Sheet *d;
    Sheet *m;
    int k;

    for (s = B_00151850; s != 0; s = s->initNext)
        func_000E47A0(s);
    for (c = B_00151848; c != 0; c = n) {
        n = c->loadNext;
        if ((c->flags & 0x3FF00000) == 0)
            func_000E2358(c);
    }
    sheetMgrResolve(1);
    if (D_00139F20 == 0) {
        D_00139F1C = 1;
        iosSleepThread();
    }
    k = 50;
    for (d = B_00151848; d != 0; d = m) {
        m = d->loadNext;
        if ((d->flags & 0x3FF00000) == 0) {
            isysRequestDeleteObj(d);
            if (--k <= 0) {
                if (D_00139F20 == 0) {
                    D_00139F1C = 1;
                    iosSleepThread();
                }
                k = 50;
            }
        }
    }
}
