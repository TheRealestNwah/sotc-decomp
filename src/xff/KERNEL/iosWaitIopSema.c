extern void WaitSema(int);
extern int B_000C3950;

void iosWaitIopSema(void)
{
    WaitSema(B_000C3950);
}
