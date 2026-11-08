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
extern void func_00006B40(void);
extern int iosCreateThreadS(void (*)(void), int, void *, int, int, int);
extern void iosStartThread(int, int);

typedef void (*PrintFn)(const char *, ...);

#ifdef NONMATCHING
/* Parked: 36 words differ (prologue order; original has nops around the
   __loader_version_id__ address load that this C does not produce) */
int ioskernel(int verbose, char *version)
{
    MemoryInfo info;
    PrintFn print = *(PrintFn volatile *)0x100000;
    PrintFn warn = *(PrintFn volatile *)0x100004;
    char *mine = __loader_version_id__;

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
#endif
