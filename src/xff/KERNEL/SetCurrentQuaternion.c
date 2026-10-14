typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
extern s128 B_00054800[];
extern int D_000409B0;

void SetCurrentQuaternion(s128 *arg0)
{
    B_00054800[D_000409B0] = *arg0;
}
