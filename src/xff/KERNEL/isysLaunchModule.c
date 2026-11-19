typedef struct Sect {
    int x0;
    int size;
    int x8;
    int addr;
    int x10;
    int x14;
    int x18;
} Sect;

typedef struct Xff {
    int magic;
    char pad04[0x14 - 0x4];
    int x14;
    char pad18[0x38 - 0x18];
    int nsect;
    int sect;
} Xff;
#define SECT(x) ((Sect *)(x)->sect)

typedef struct Module {
    char pad00[0x1C];
    Xff *xff;
    char pad20[0x38 - 0x20];
    char *name;
    int x3C;
} Module;

extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern void iosResetCpuRapCounter(int);
extern float iosGetCpuRapCountPar1Int(void);
extern int func_00007E00(void *);
extern void func_00007810(void *, int);
extern int func_0000A748(void *, int, int);
extern char needResolveModuleGroup[];
extern int iosSPrintf(char *, const char *, ...);
extern void OutputLinkerScriptFile(Xff *, char *, int (*)(const char *, ...));
extern int printf(const char *, ...);
extern volatile int D_00040900;
extern int D_STR_00040908;

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

static inline int resolve_all(void *group)
{
    int count = 0;
    char *object = 0;
    void **link;

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

void isysLaunchModule(Module *m)
{
    char buf[0x400];
    Xff *x, *y;
    int size;
    int n;
    int i;

    resolve_all(needResolveModuleGroup);
    y = m->xff;
    iosSPrintf(buf, "%s.cmd", m->name);
    OutputLinkerScriptFile(y, buf, printf);
    size = 0;
    x = m->xff;
    if (x->magic == D_STR_00040908) {
        n = x->nsect >> 1;
        for (i = 0; i < n; i++)
            size += SECT(x)[i].size;
        func_0000A748(x, SECT(x)[0].addr + size * 8, 0);
        for (i = 0; i < n; i++)
            SECT(x)[n + i].size = 0;
        size = x->x14 - (SECT(x)[n].addr - (int)x);
    }
    m->x3C -= size;
    D_00040900 -= size;
}
