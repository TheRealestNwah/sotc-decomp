extern int B_000DE338[];
extern int DIntr(void);
extern int EIntr(void);

void Sg2SlotSetKeyOffBit(int i, int bits)
{
    int s = DIntr();
    B_000DE338[i] |= bits;
    if (s)
        EIntr();
}
