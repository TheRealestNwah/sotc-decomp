typedef struct { char pad[0x10]; volatile int ptr; } PathState;
extern PathState B_00065018;

int iosAllocPacketPtrPath1(int size)
{
    int packet = B_00065018.ptr;

    B_00065018.ptr += size;
    /* noreorder keeps the prefetch out of the return's delay slot. */
    __asm__ __volatile__(".set noreorder\n"
                         "pref 0, 0x40(%0)\n"
                         ".set reorder" : : "r"(packet));
    return packet;
}
