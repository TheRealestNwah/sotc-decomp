typedef struct { int start[2]; int c, d; int ptr; int e; int cur; } DlState;
extern volatile DlState B_00065018;
extern int D_00040AFC;

int iosDlGetEndAdrs(void)
{
    volatile DlState *dl = &B_00065018;

    return dl->start[dl->cur] + D_00040AFC * 16 - 0x1000;
}
