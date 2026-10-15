extern int B_0004F5F8;
extern void WaitSema(int);
extern void SignalSema(int);
static void *func_00002AB8(void *, int, void *);

void *iosCreatePartition(void *a, int size)
{
    void *r;
    register void *ra __asm__("$31");
    void *t = ra;
    WaitSema(B_0004F5F8);
    r = func_00002AB8(a, size, t);
    SignalSema(B_0004F5F8);
    return r;
}
