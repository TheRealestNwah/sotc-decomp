extern void LoaderSysEntryExternalIopMemoryList(int);
extern void iosSignalIopSema();
extern void iosWaitIopSema();
extern int sceSifAllocIopHeap(int);

int iosAllocIopHeap(int arg0)
{
    int temp_s0;

    iosWaitIopSema();
    temp_s0 = sceSifAllocIopHeap(arg0);
    iosSignalIopSema();
    if (temp_s0 != 0) {
        iosWaitIopSema();
        LoaderSysEntryExternalIopMemoryList(temp_s0);
        iosSignalIopSema();
    }
    return temp_s0;
}
