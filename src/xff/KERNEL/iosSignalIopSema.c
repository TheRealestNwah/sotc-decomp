extern void SignalSema(int);
extern int B_000C3950;

void iosSignalIopSema(void)
{
    SignalSema(B_000C3950);
}
