extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern void iosResetCpuRapCounter(int);
extern float iosGetCpuRapCountPar1Int(void);
extern int func_00007E00(void *);
extern void func_00007810(void *, int);

#ifdef NONMATCHING
/* Parked: 19 words differ (s0/s1/s2 register allocation for object, link, pending) */
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

int isysResolveAllModuleObjOfGroup(void *group)
{
    char *object = 0;
    void **link;
    int count = 0;

    for (link = isysGroupForFirst(group, 0); link != 0; link = isysGroupForNext(link, 0)) {
        object = *link;
        resolve_module(object);
        count++;
    }
    if (object != 0) {
        isysGroupForExit(object, 0);
    }
    return count;
}
#endif
