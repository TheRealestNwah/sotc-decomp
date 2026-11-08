typedef struct { char pad0[0x1C]; volatile int v; } PathState;
extern PathState B_00065018;

int iosDlGetLayer(void)
{
    return B_00065018.v;
}
