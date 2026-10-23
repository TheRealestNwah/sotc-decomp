extern int B_0004F5F8;
extern void WaitSema(int);
extern void SignalSema(int);
extern void func_00003028(void *, int, int, int);

void iosDebugPartitionDump(void *partition, int flags)
{
    WaitSema(B_0004F5F8);
    func_00003028(partition, 0, flags, -1);
    SignalSema(B_0004F5F8);
}
