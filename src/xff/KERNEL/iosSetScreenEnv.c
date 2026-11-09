typedef unsigned long long u64;

typedef struct {
    int pad0[2];
    unsigned int b0 : 1;
    unsigned int b1 : 4;
    unsigned int b5 : 1;
    unsigned int rest : 26;
    char padC[0x2C];
} ScrCtx;

typedef struct {
    char pad0[0x10];
    ScrCtx ctx[2];
    char pad80[0x20];
    unsigned int flag : 1;
} ScrEnv;

extern volatile int D_00040B40[4];
extern short D_00040B30, D_00040B34, D_00040B38;
extern ScrEnv B_00065550;
extern void waitVscheduler();
extern void iosGsSetMode(void);
extern int sceGsResetGraph(short, short, short, short);
extern void func_00014948(void);
extern void iosSetRootContext(void);
extern void func_00014BD8(void);

void iosSetScreenEnv(void)
{
    int stat;
    volatile u64 *csr;
    u64 tmp;
    int i;
    short inter, omode, ffmode;
    ScrEnv *e;

    D_00040B40[2] = 0;
    D_00040B40[1] = D_00040B40[2];
    D_00040B40[0] = D_00040B40[1];
    D_00040B40[3] = 0x80;
    do {
        __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(stat));
    } while ((*(volatile int *)0x10009000 & 0x100) || (*(volatile int *)0x1000A000 & 0x100) ||
             (*(volatile int *)0x10003C00 & 0x1F000003) || (stat & 0x100) || (*(volatile int *)0x10003020 & 0xC00));
    waitVscheduler();
    csr = (volatile u64 *)0x12001000;
    tmp = *csr;
    iosGsSetMode();
    inter = D_00040B30;
    omode = D_00040B34;
    ffmode = D_00040B38;
    *csr = 0x200;
    sceGsResetGraph(0, inter & 1, omode, ffmode & 1);
    func_00014948();
    iosSetRootContext();
    e = &B_00065550;
    for (i = 0; i < 2; i++) {
        e->ctx[i].b0 = e->flag;
        e->ctx[i].b5 = e->flag;
    }
    func_00014BD8();
}
