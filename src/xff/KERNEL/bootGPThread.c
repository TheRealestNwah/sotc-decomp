extern void InitDL(int, int);
extern long iosGetTCount(void);
extern int sceGsGetIMR(void);
extern int sceGsPutIMR(int);
extern void iosAddIntcHandler(int, int (*)(void));
extern void iosSetScreenEnv(void);
extern int iosCreateThread(void (*)(void), void *, int, int, int);
extern void iosStartThread(int, int);
extern void set_nowloadingflag(int);
extern void iosSyncV(int);
extern int func_00016E90(void);
extern void func_00016F78(void);
extern volatile long B_00065610;
extern int B_00065618;
extern char B_00065620[];
extern int D_00040BC8;

void bootGPThread(int arg)
{
    InitDL(0x7C80, 0x20);
    B_00065610 = iosGetTCount();
    *(volatile long *)0x12001000 |= 2;
    sceGsPutIMR(sceGsGetIMR() & ~0x200);
    iosAddIntcHandler(0, func_00016E90);
    iosSetScreenEnv();
    D_00040BC8 = arg;
    B_00065618 = iosCreateThread(func_00016F78, B_00065620, 0x8000, 0x2A, 0);
    iosStartThread(B_00065618, 0);
    set_nowloadingflag(1);
    iosSyncV(0);
}
