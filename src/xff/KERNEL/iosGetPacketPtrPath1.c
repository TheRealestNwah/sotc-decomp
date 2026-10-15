typedef struct { char pad[0x10]; volatile int ptr; } PathState;
extern PathState B_00065018;

int iosGetPacketPtrPath1(void)
{
    if (B_00065018.ptr & 0xF)
        B_00065018.ptr = B_00065018.ptr - (B_00065018.ptr & 0xF) + 0x10;
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(B_00065018.ptr));
    return B_00065018.ptr;
}
