typedef struct { char pad[0xA0]; int a; int b; } GpState;
extern GpState B_00065550;
extern void sceGsResetPath(void);
extern void sceGsSyncPath(int, int);
extern void iosInitDC(void);

void InitGp(void)
{
    sceGsResetPath();
    sceGsSyncPath(0, 0);
    iosInitDC();
    B_00065550.a = 1;
    B_00065550.b = 0;
}
