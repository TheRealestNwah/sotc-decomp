typedef struct { char pad0[0x18]; volatile int v; } PathState;
extern PathState B_00065018;

int iosDlGetWorkBufId(void)
{
    return B_00065018.v;
}
