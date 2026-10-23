extern int B_0004F5F8;
extern int gbPtn;
extern void WaitSema(int);
extern void SignalSema(int);
static void *func_00001460(int, int, int, void *);

void *iosMallocInGarbagePtn(int size, int align)
{
    void *r;
    register void *ra __asm__("$31");
    void *t = ra;
    WaitSema(B_0004F5F8);
    r = func_00001460(gbPtn, size, align < 16 ? 16 : align, t);
    if (r != 0) {
        ((int **)r)[-1][4] |= 0xFFFFFF;
    }
    SignalSema(B_0004F5F8);
    return r;
}
