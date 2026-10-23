extern int B_0004F5F8;
extern void WaitSema(int);
extern void SignalSema(int);
static void *func_00001460(int, int, int, void *);

void *iosMallocAlignNoCheck(int a, int b, int c)
{
    void *r;
    register void *ra __asm__("$31");
    void *t = ra;
    WaitSema(B_0004F5F8);
    r = func_00001460(a, b, c, t);
    SignalSema(B_0004F5F8);
    return r;
}
