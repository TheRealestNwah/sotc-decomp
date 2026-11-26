extern char rootPtn[];
extern int B_000C3950;

extern void LoaderSysEntryExternalIopMemoryList(int);
extern int LoaderSysDeleteExternalIopMemoryList(int);
extern int LoaderSysLoadIopModuleFromEEBuffer(void *, void *, int, int, int);
extern int LoaderSysCheckCDBootMode();
extern int sceSifAllocIopHeap(int);
extern void sceSifFreeIopHeap(int);
extern void sceSifInitRpc(int);
extern void sceSifInitIopHeap(void);
extern int sceSifQueryTotalFreeMemSize(void);
extern int iosLoaderFOpen(void *, int, int);
extern int iosLoaderGetFileSize(int);
extern int iosLoaderFRead();
extern int iosLoaderFClose(int);
extern void *iosMallocAlign(void *, int, int);
extern void iosFree(void *);
extern void WaitSema(int);
extern void SignalSema(int);

void iosWaitIopSema(void);
void iosSignalIopSema(void);

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

int iosLoadIopModule(void *path, void *name, int args, int argp)
{
    int fd = iosLoaderFOpen(path, 1, 0);
    int size;
    void *buffer;
    int result;
    if (fd < 0) {
        return -1;
    }
    size = iosLoaderGetFileSize(fd);
    buffer = iosMallocAlign(rootPtn, size, 64);
    iosLoaderFRead(fd, buffer, size);
    result = LoaderSysLoadIopModuleFromEEBuffer(name, buffer, size, args, argp);
    iosFree(buffer);
    iosLoaderFClose(fd);
    return result;
}

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

int iosGetIopTotalMemSize(void)
{
    return LoaderSysCheckCDBootMode() == 0 ? 0x800000 : 0x200000;
}

void iosWaitIopSema(void)
{
    WaitSema(B_000C3950);
}

void iosSignalIopSema(void)
{
    SignalSema(B_000C3950);
}
