extern void iosWaitIopSema(void);
extern void iosSignalIopSema(void);
extern void sceSifInitRpc(int);
extern void sceSifInitIopHeap(void);
extern int sceSifQueryTotalFreeMemSize(void);

int iosGetIopTotalFreeMemSize(void)
{
    int r;
    iosWaitIopSema();
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    r = sceSifQueryTotalFreeMemSize();
    iosSignalIopSema();
    return r;
}
