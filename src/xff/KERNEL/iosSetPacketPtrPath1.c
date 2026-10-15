typedef struct {
    int a, b;
    int adrs[2];
    int ptr;
    int e;
    int cur;
} DlBufs;

extern volatile DlBufs B_00065018;

void iosSetPacketPtrPath1(int p)
{
    volatile DlBufs *dl = &B_00065018;

    dl->ptr = p;
}
