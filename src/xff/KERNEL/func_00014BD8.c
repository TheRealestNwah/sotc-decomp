/* Writes the current display environment to the GS privileged registers and flips the buffer index. */
typedef unsigned long u_long64 __attribute__((mode(DI)));

typedef struct {
    u_long64 v;
} GsReg;

typedef struct {
    GsReg pmode;
    GsReg smode2;
    GsReg dispfb2;
    GsReg display2;
    GsReg dispfb1;
    GsReg display1;
    GsReg bgcolor;
} DispEnv;

typedef struct {
    char pad0[0x18];
    DispEnv env[2];
    char pad88[4];
    volatile int flip;
} DispWork;

extern DispWork B_00065550;

static void func_00014BD8(void)
{
    int flip = B_00065550.flip;
    int i = flip & 1;

    *(volatile u_long64 *)0x12000000 = *(u_long64 *)&B_00065550.env[i].pmode;
    *(volatile u_long64 *)0x12000020 = *(u_long64 *)&B_00065550.env[i].smode2;
    *(volatile u_long64 *)0x12000090 = *(u_long64 *)&B_00065550.env[i].dispfb2;
    *(volatile u_long64 *)0x12000070 = *(u_long64 *)&B_00065550.env[i].dispfb1;
    *(volatile u_long64 *)0x120000A0 = *(u_long64 *)&B_00065550.env[i].display2;
    *(volatile u_long64 *)0x12000080 = *(u_long64 *)&B_00065550.env[i].display1;
    *(volatile u_long64 *)0x120000E0 = *(u_long64 *)&B_00065550.env[i].bgcolor;
    B_00065550.flip = flip ^ 1;
}
