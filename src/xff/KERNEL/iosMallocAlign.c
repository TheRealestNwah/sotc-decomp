extern int B_0004F5F8;
extern int D_00040648;
extern int gbPtn;
extern unsigned char rootPtn[];
extern char RO_00042008[];
extern char RO_00042038[];
extern char RO_00042068[];
extern char RO_00042078[];
extern void WaitSema(int);
extern void SignalSema(int);
extern void LoaderSysPrintf(const char *, ...);
extern void iosJumpRecoverPoint(void *, ...);
static void *func_00001460(int, int, int, void *);
static void func_00003D28(int, int);

void *iosMallocAlign(int ptn, int size, int align)
{
    void *r;
    register void *ra __asm__("$31");
    void *t = ra;
    WaitSema(B_0004F5F8);
    r = func_00001460(ptn, size, align, t);
    if (r == 0) {
        LoaderSysPrintf(RO_00042008, ptn, size, t);
        func_00003D28(ptn, 1);
        LoaderSysPrintf(RO_00042038, rootPtn, gbPtn);
    }
    SignalSema(B_0004F5F8);
    if (r == 0) {
        LoaderSysPrintf(RO_00042068, D_00040648);
        if (D_00040648) {
            ((void (*)(void))D_00040648)();
        }
        iosJumpRecoverPoint(RO_00042078, ptn, size, t);
    }
    return r;
}
