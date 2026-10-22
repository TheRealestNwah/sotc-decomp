extern int LoaderSysDeleteExternalIopMemoryList(int);
extern void iosSignalIopSema();
extern void iosWaitIopSema();
extern void sceSifFreeIopHeap(int);

int iosFreeIopHeap(int p)
{
    int r;

    iosWaitIopSema();
    sceSifFreeIopHeap(p);
    r = LoaderSysDeleteExternalIopMemoryList(p);
    p = -1;
    if (r >= 0) {
        p = 0;
    }
    iosSignalIopSema();
    return p;
}
