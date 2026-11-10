extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;
extern int Sg2SlotFindSlotClassCh(int *, int, int);
extern void Sg2SlotSetBendValue(int, int);

static void func_00024F80(void)
{
    int slots[48];
    unsigned char *ev = B_000C5C0C;
    int ch = ev[0] & 0xF;
    int bend = ev[1] + (ev[2] << 7);
    char *p = B_000C5C10 + 4;
    int i;

    bend >>= 7;
    *(int *)(p + ch * 0x70 + 0x2E0) = bend;
    for (i = Sg2SlotFindSlotClassCh(slots, *(int *)p, ch) - 1; i >= 0; i--) {
        Sg2SlotSetBendValue(slots[i], bend);
    }
}
