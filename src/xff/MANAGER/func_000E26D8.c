typedef struct Sheet {
    char pad0[0x44];
    unsigned int flags;
    char pad48[4];
    struct Sheet *loadNext;
    struct Sheet *initNext;
} Sheet;

extern Sheet *B_00151848;
extern Sheet *B_00151850;
extern int D_00139F1C;
extern int D_00139F20;
extern void func_000E47A0(Sheet *);
extern void func_000E2358(Sheet *);
extern void sheetMgrResolve(int);
extern int iosSleepThread(void);
extern void isysRequestDeleteObj(void *);

/* Resolves pending sheets, then requests deletion of every idle loaded sheet, sleeping every 50 deletions. */
static void func_000E26D8(void)
{
    Sheet *s;
    int count;

    for (s = B_00151850; s != 0; s = s->initNext)
        func_000E47A0(s);
    {
        Sheet *p = B_00151848, *n;

        while (p != 0) {
            n = p->loadNext;
            if (!(p->flags & 0x3FF00000))
                func_000E2358(p);
            p = n;
        }
    }
    sheetMgrResolve(1);
    if (D_00139F20 == 0) {
        D_00139F1C = 1;
        iosSleepThread();
    }
    count = 50;
    {
        Sheet *p = B_00151848, *n;

        for (; p != 0; p = n) {
            n = p->loadNext;
            if (!(p->flags & 0x3FF00000)) {
                isysRequestDeleteObj(p);
                if (--count <= 0) {
                    if (D_00139F20 == 0) {
                        D_00139F1C = 1;
                        iosSleepThread();
                    }
                    count = 50;
                }
            }
        }
    }
}
