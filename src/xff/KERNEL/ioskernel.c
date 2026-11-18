typedef char *va_list;
#define va_start(ap, last) (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))
extern int vsprintf(char *, const char *, va_list);
extern void LoaderSysJumpRecoverPoint(char *);

typedef struct {
    char pad0[0x18];
    int start;
    int size;
    char pad20[0x50];
} MemoryInfo;

extern char __loader_version_id__[];
extern char RO_00042770[];
extern char RO_000427C0[];
extern char RO_000427E8[];
extern char RO_00042810[];
extern char RO_00042840[];
extern char RO_000428A0[];
extern char rootPtn[];
extern int B_00053F08;
extern char B_00053B08[];

extern double atof(const char *);
extern void LoaderSysGetMemoryInfo(MemoryInfo *);
extern void iosInitIntrSystem(void);
extern void iosInitMallocSystem(int, int, int);
extern void initDldSys(void);
extern void InitMath(void);
extern int InitNet(void);
extern void InitGp(void);
extern void iosInit(void);
extern void isysInitObjSystem(void);
extern void InitDld(void);
extern void InitIopDev(void);
extern void InitSubThread(void);
static void func_00006B40(void);
extern int iosCreateThreadS(void (*)(void), int, void *, int, int, int);
extern void iosStartThread(int, int);

extern int LoaderSysResetSystem();

extern void IosLoadIrxSimulation(void);
extern void initSound(void);
extern void iosMcInit(void);
extern void bootSchedulerThread(void);
extern void iosMouseInit(void);
extern void iosKeybdInit(void);
extern void IosCdvdManagerSimulation(void);
extern void iosDeleteThread(int);

typedef void (*PrintFn)(const char *, ...);

int ioskernel(int verbose, char *version)
{
    MemoryInfo info;
    PrintFn print = *(PrintFn *)0x100000;
    PrintFn warn = *(PrintFn *)0x100004;
    char *mine;

    /* The Original loads this address with nops around the %lo half, which
       gcc never emits for a symbol address. */
    __asm__ volatile("lui %0, %%hi(__loader_version_id__)
	"
                     "nop
	"
                     "addiu %0, %0, %%lo(__loader_version_id__)
	"
                     "nop"
                     : "=r"(mine));

    if (verbose) {
        print(RO_00042770);
        print(RO_000427C0, version);
        print(RO_000427E8, mine);
        if (version == mine) {
            print(RO_00042810);
        } else {
            warn(RO_00042840, version, mine);
        }
    }
    atof(RO_000428A0);
    LoaderSysGetMemoryInfo(&info);
    iosInitIntrSystem();
    iosInitMallocSystem(info.start, info.size, 0xDAE000);
    initDldSys();
    InitMath();
    InitNet();
    InitGp();
    iosInit();
    isysInitObjSystem();
    InitDld();
    InitIopDev();
    InitSubThread();
    B_00053F08 = iosCreateThreadS(func_00006B40, 0, rootPtn, 0x10000, 0x2D, 0);
    iosStartThread(B_00053F08, 0);
    return 0;
}

void iosJumpRecoverPoint(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsprintf(B_00053B08, fmt, ap);
    LoaderSysJumpRecoverPoint(B_00053B08);
}

int iosResetKernel(int a, int b, int c, int d)
{
    return LoaderSysResetSystem(a, b, c, d);
}

static void func_00006B40(void)
{
    IosLoadIrxSimulation();
    initSound();
    iosMcInit();
    bootSchedulerThread();
    iosMouseInit();
    iosKeybdInit();
    IosCdvdManagerSimulation();
    iosDeleteThread(0);
}
