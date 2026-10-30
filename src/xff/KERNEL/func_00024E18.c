extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;
extern int Sg2SlotFindSlotClassCh(int *slots, int cls, int ch);
extern void Sg2SlotSetKeyOffBit(int i, int bits);

static void func_00024E18(void)
{
    int slots[48];
    int i;
    int slot;

    i = Sg2SlotFindSlotClassCh(slots, *(int *)(B_000C5C10 + 4), B_000C5C0C[0] & 0xF) - 1;
    for (; i >= 0; i--) {
        slot = slots[i];
        Sg2SlotSetKeyOffBit(slot >= 24, slot < 24 ? 1 << slot : 1 << (slot - 24));
    }
}
