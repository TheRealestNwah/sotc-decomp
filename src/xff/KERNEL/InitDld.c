extern unsigned char rootPtn[];
extern char B_00054398[], B_00054330[];
extern char executableModuleGroup[], needResolveModuleGroup[], symbolDefModuleGroup[];
extern void iosCdInit(void);
extern void InitStrHash(void *hash, void *ptn, int size);
extern void isysInitGroup(void *group);
extern void LoaderSysGetMemoryInfo(void *info);
extern void func_00008CE0(void *a, int b, void *ptn);
extern void isysCreateExceptionThread(void);

void InitDld(void)
{
    iosCdInit();
    InitStrHash(B_00054398, rootPtn, 0x10000);
    isysInitGroup(executableModuleGroup);
    isysInitGroup(needResolveModuleGroup);
    isysInitGroup(symbolDefModuleGroup);
    LoaderSysGetMemoryInfo(B_00054330);
    func_00008CE0(B_00054330 + 0x20, *(int *)(B_00054330 + 0x64), rootPtn);
    isysCreateExceptionThread();
}
