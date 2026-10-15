typedef int s128 __attribute__((mode(TI)));
extern int D_000409B0;
extern s128 B_00054800[];
extern void InitQuaternionDrive(void);

void PushQuaternion(void)
{
    int *p = &D_000409B0;
    if (*p < 0)
        InitQuaternionDrive();
    if (++*p >= 0x40)
        *p = 0x3F;
    B_00054800[*p] = *(&B_00054800[*p] - 1);
}
