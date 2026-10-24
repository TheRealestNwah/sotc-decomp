extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern void iosResetCpuRapCounter(int);
extern float iosGetCpuRapCountPar1Int(void);
extern long iosGetTCount(void);
static int func_00007E00(void *);
static void func_00007810(void *, int);
extern char needResolveModuleGroup[];
extern char executableModuleGroup[];
static inline int resolve_module(char *object)
{
    int pending;
    iosResetCpuRapCounter(2);
    pending = func_00007E00(object);
    iosGetCpuRapCountPar1Int();
    if (*(int *)(object + 0x2C) & 0x20000000) {
        if (pending != 0) {
            func_00007810(object, 0);
        }
    } else {
        func_00007810(object, 1);
        *(int *)(object + 0x2C) |= 0x20000000;
    }
    iosGetCpuRapCountPar1Int();
    return pending;
}
void isysDumpExecutableModules(void)
{
    void *object = 0;
    void **link;
    for (link = isysGroupForFirst(executableModuleGroup, 0); link != 0;
         link = isysGroupForNext(link, 0)) {
        object = *link;
    }
    if (object != 0) {
        isysGroupForExit(object, 0);
    }
}

int isysResolveAllModuleObjHasUndefSymbol(void)
{
    char *object = 0;
    void **link;
    iosGetTCount();
    for (link = isysGroupForFirst(needResolveModuleGroup, 0); link != 0; link = isysGroupForNext(link, 0)) {
        object = *link;
        resolve_module(object);
    }
    if (object != 0) {
        isysGroupForExit(object, 0);
    }
    return 1;
}
int isysResolveOneModuleObj(void *object)
{
    return resolve_module(object);
}
int isysResolveAllProgramModule(void)
{
    char *object = 0;
    void **link;
    iosGetTCount();
    for (link = isysGroupForFirst(executableModuleGroup, 0); link != 0; link = isysGroupForNext(link, 0)) {
        object = *link;
        resolve_module(object);
    }
    if (object != 0) {
        isysGroupForExit(object, 0);
    }
    return 1;
}

