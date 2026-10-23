typedef struct { char pad[0x10]; volatile int ptr; } PathState;
extern PathState B_00065018;

int iosAllocPacketPtrPath1UnCachedA(int size)
{
    int packet = B_00065018.ptr;

    B_00065018.ptr += size;
    return packet | 0x30000000;
}
