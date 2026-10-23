extern void iosPadInit(void);
extern void iosCreateIVArbitrationSema(void);
extern int *iosCreateThread(void *, void *, int, int, int);
extern int iosStartThread(int *, void *);
extern int iosAddIntcHandler(int, void *);
extern int D_00040D70;
extern char D_0001B740[], D_0001B820[];
extern void func_0001B180(void);
extern char B_000BF710[], B_000C0750[];
extern int *B_000BF704, *B_000C0748;

void bootSchedulerThread(void)
{
    iosPadInit();
    D_00040D70 = 0;
    iosCreateIVArbitrationSema();
    B_000BF704 = iosCreateThread(D_0001B740, B_000BF710, 0x1000, 0x28, 0);
    iosStartThread(B_000BF704, 0);
    iosAddIntcHandler(2, D_0001B820);
    B_000C0748 = iosCreateThread(func_0001B180, B_000C0750, 0x2000, 0x2D, 0);
    iosStartThread(B_000C0748, 0);
}
