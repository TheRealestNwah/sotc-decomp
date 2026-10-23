typedef int s128 __attribute__((mode(TI)));

extern s128 B_00054800[];
extern int D_000409B0;

s128 *GetCurrentQuaternion(void)
{
    return &B_00054800[D_000409B0];
}
