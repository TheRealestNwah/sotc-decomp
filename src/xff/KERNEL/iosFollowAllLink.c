extern int B_0004F5F8;
extern void WaitSema(int);
extern void SignalSema(int);
extern void func_00003330(void *, int, int *);

int iosFollowAllLink(void *a)
{
    int n = 0;
    WaitSema(B_0004F5F8);
    func_00003330(a, 0, &n);
    SignalSema(B_0004F5F8);
    return n;
}
