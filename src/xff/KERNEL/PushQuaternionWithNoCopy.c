extern int D_000409B0;
extern void InitQuaternionDrive(void);

void PushQuaternionWithNoCopy(void)
{
    if (D_000409B0 < 0) {
        InitQuaternionDrive();
    }
    D_000409B0++;
    if (D_000409B0 >= 0x40) {
        D_000409B0 = 0x3F;
    }
}
