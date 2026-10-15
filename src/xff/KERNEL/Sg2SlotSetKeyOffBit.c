extern int B_000DE338[];
extern int DIntr(void);
extern void EIntr(void);

void Sg2SlotSetKeyOffBit(int i, int bits)
{
    int s = DIntr();
    B_000DE338[i] |= bits;
    if (s)
        EIntr();
}
