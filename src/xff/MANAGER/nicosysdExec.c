extern void SignalSema(int);
extern void WaitSema(int);
extern void func_000DF038(int, int);
extern void func_000DF1B0(int);
extern int B_001506E4;
extern int D_00139EF0;

void nicosysdExec(int arg0, int arg1, int arg2)
{
    if (D_00139EF0 != 0) {
        WaitSema(B_001506E4);
        func_000DF1B0(arg0);
        func_000DF038(arg1, arg2);
        SignalSema(B_001506E4);
    }
}
