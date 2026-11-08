typedef struct { char pad0[0x14]; volatile int v; } PathState;
extern PathState B_00065018;

int iosDlGetLayerNum(void)
{
    return B_00065018.v;
}
