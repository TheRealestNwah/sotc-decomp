typedef struct { int start[2]; int c, d; int ptr; int e; int cur; } DlState;
extern volatile DlState B_00065018;
extern int D_00040AFC;

int iosDlCheckSize(void)
{
    int end = B_00065018.start[B_00065018.cur] + D_00040AFC * 16 - 0x1000;
    if (B_00065018.ptr & 0xF)
        B_00065018.ptr = B_00065018.ptr - (B_00065018.ptr & 0xF) + 16;
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(B_00065018.ptr));
    return end - B_00065018.ptr;
}
