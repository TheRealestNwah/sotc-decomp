extern void WaitSema(int);
extern int B_0004F5F8;

void iosWaitMalloc(void)
{
    WaitSema(B_0004F5F8);
}
