extern void SignalSema(int);
extern void WaitSema(int);
extern int func_00002868(int, int, int, int);
extern int B_0004F5F8;

int iosReallocAlign(int arg0, int arg1, int arg2, int arg3)
{
    int temp_s1;

    WaitSema(B_0004F5F8);
    temp_s1 = func_00002868(arg0, arg1, arg2, arg3);
    SignalSema(B_0004F5F8);
    return temp_s1;
}
