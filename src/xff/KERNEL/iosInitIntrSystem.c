typedef struct { int count; int max_count; int init_count; int wait_threads; int attr; int option; } SemaParam;
extern int CreateSema(SemaParam *);
extern void LoaderSysEntryExternalSemaList(int);

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

static int func_00000EF0(int);
extern int iosAddIntcHandler(int, int (*)(int));
extern int iosSystemSema;
extern int B_0004F5E8, B_0004F5EC;
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

extern volatile long B_0004F5E0;
static int func_00000EF0(int cause)
{
    B_0004F5E0 += 0x10000;
    *(volatile unsigned int *)0x10000010 = 0xA80;
    __asm__ __volatile__("sync\n" "ei\n" : : : "memory");
    return 0;
}
