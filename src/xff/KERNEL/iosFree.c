extern void SignalSema(int);
extern void WaitSema(int);
extern void func_00002050(int);
extern int B_0004F5F8;

void iosFree(int arg0)
{
    WaitSema(B_0004F5F8);
    func_00002050(arg0);
    SignalSema(B_0004F5F8);
}
