/* Matches only with -fno-strict-aliasing (config/ee_cflags.json), for
   iosAddIntcHandler. */
typedef struct {
    int id;
    int intc;
    int (*handler)(int);
} IntcEntry;
typedef struct { int count; int max_count; int init_count; int wait_threads; int attr; int option; } SemaParam;
typedef void (*ResetCallback)(void);

extern IntcEntry D_000405A0[];
extern int D_00040624;
extern float D_00040628[];
extern int D_00040634;
extern char RO_00041ED8[];
extern char RO_00041F20[];
extern char RO_00041F68[];
extern char RO_00041F80[];
extern char RO_00041F98[];
extern char RO_00041FC8[];
extern char RO_00041FE0[];
extern volatile long B_0004F5E0;
extern int B_0004F5E8, B_0004F5EC;
extern ResetCallback B_0004F5F0[];
extern int iosSystemSema;
extern void iosJumpRecoverPoint(const char *, ...);
extern int AddIntcHandler(int, int (*)(int), int);
extern void LoaderSysEntryExternalIntcHandlerList(int, int);
extern int EnableIntc(int);
extern int CreateSema(SemaParam *);
extern int DeleteSema(int sema);
extern void LoaderSysEntryExternalSemaList(int);
extern void LoaderSysDeleteExternalSemaList(int sema);
extern int DIntr();
extern int EIntr(void);
extern void loaderSetResetCallback(ResetCallback);

static int func_00000EF0(int);
static void func_00000F28(void);

void iosAddIntcHandler(int id, int (*handler)(int))
{
    unsigned int i;

    for (i = 0; i < 11; i++) {
        if (D_000405A0[i].id == id)
            goto found;
    }
    iosJumpRecoverPoint(RO_00041ED8);
    return;
found:
    if (D_000405A0[i].handler) {
        iosJumpRecoverPoint(RO_00041F20);
        return;
    }
    D_000405A0[i].handler = handler;
    LoaderSysEntryExternalIntcHandlerList(AddIntcHandler(D_000405A0[i].intc, handler, 0), D_000405A0[i].intc);
    EnableIntc(D_000405A0[i].intc);
}

int iosCreateSema(int init, int max, int unused)
{
    SemaParam p;
    int s;
    p.init_count = init;
    p.max_count = max;
    s = CreateSema(&p);
    LoaderSysEntryExternalSemaList(s);
    return s;
}

int iosDeleteSema(int sema)
{
    LoaderSysDeleteExternalSemaList(sema);
    return DeleteSema(sema);
}

static inline int createSystemSema(int init, int max, int unused)
{
    SemaParam p;
    int s;
    p.init_count = init;
    p.max_count = max;
    s = CreateSema(&p);
    LoaderSysEntryExternalSemaList(s);
    return s;
}

void iosInitIntrSystem(void)
{
    *(volatile unsigned int *)0x10000010 = 0;
    *(volatile unsigned int *)0x10000810 = 0;
    iosAddIntcHandler(9, func_00000EF0);
    *(volatile unsigned int *)0x10000000 = 0;
    *(volatile unsigned int *)0x10000800 = 0;
    *(volatile unsigned int *)0x10000010 = 0x280;
    *(volatile unsigned int *)0x10000810 = 0x80;
    iosSystemSema = createSystemSema(1, 1, 0);
    B_0004F5E8 = -1;
    B_0004F5EC = 0;
}

long iosGetTCount(void)
{
    return B_0004F5E0;
}

long iosGetTCountExtension(void)
{
    return B_0004F5E0 | (unsigned int)*(volatile int *)0x10000000;
}

float iosGetSecondFromTCount(unsigned long ticks)
{
    unsigned long seconds = ticks / 150000000UL;
    ticks -= seconds * 150000000UL;
    return (float)seconds + (float)ticks * (1.0f / 150000000.0f);
}

void iosResetCpuRapCounter(int mode)
{
    D_00040624 = mode;
    *(volatile int *)0x10000810 = mode | 0x80;
    *(volatile int *)0x10000800 = 0;
}

float iosGetCpuRapCountPar1Int(void)
{
    return (float)*(volatile unsigned int *)0x10000800 * 60.0f / D_00040628[D_00040624];
}

void iosDI(void)
{
    if (DIntr() != 0) {
        if (D_00040634 != 0) {
            iosJumpRecoverPoint(RO_00041F68, D_00040634);
        }
    } else if (D_00040634 <= 0) {
        iosJumpRecoverPoint(RO_00041F80, D_00040634);
    }
    D_00040634 += 1;
}

int iosEI(void)
{
    int temp_v0;

    temp_v0 = D_00040634 - 1;
    D_00040634 = temp_v0;
    if (temp_v0 == 0) {
        if (EIntr() != 0) {
            iosJumpRecoverPoint(RO_00041F98);
        }
    } else if (temp_v0 < 0) {
        iosJumpRecoverPoint(RO_00041FC8);
    }
    return D_00040634;
}

void iosLoaderResetEntry(ResetCallback fn)
{
    int i;

    if (B_0004F5F0[0] == 0) {
        loaderSetResetCallback(func_00000F28);
    }
    for (i = 0; i < 2; i++) {
        if (B_0004F5F0[i] == 0) {
            goto found;
        }
    }
    iosJumpRecoverPoint(RO_00041FE0);
found:
    B_0004F5F0[i] = fn;
}

static int func_00000EF0(int cause)
{
    B_0004F5E0 += 0x10000;
    *(volatile unsigned int *)0x10000010 = 0xA80;
    __asm__ __volatile__("sync\n" "ei\n" : : : "memory");
    return 0;
}

static void func_00000F28(void)
{
    ResetCallback *next = B_0004F5F0;
    int remaining;
    for (remaining = 1; remaining >= 0; remaining--) {
        ResetCallback callback = *next++;
        if (callback != 0)
            callback();
    }
}
