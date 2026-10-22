extern int B_0004F5F8;
extern void WaitSema(int);
extern void SignalSema(int);
extern void func_00003028(void *, int, int, int);

void iosDebugPartitionFileDump(void *partition, int flags, int output)
{
    WaitSema(B_0004F5F8);
    func_00003028(partition, 0, flags, output);
    SignalSema(B_0004F5F8);
}
