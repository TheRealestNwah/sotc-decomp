extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;
extern int Sg2SlotFindSlotClassCh(int *slots, int cls, int ch);
extern void Sg2SlotSetLfoPitchDepth(int slot, int value);

static void func_00024450(void)
{
    int slots[48];
    char *st;
    int ch;
    int i;

    st = B_000C5C10;
    ch = B_000C5C0C[0] & 0xF;
    *(int *)(st + ch * 0x70 + 0x300) = B_000C5C0C[2];
    i = Sg2SlotFindSlotClassCh(slots, *(int *)(st + 4), ch) - 1;
    for (; i >= 0; i--) {
        Sg2SlotSetLfoPitchDepth(slots[i], B_000C5C0C[2]);
    }
}
