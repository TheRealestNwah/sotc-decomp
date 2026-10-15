extern int B_000DE330[];
extern int DIntr(void);
extern void EIntr(void);

void Sg2SlotSetKeyOnBit(int i, int bits)
{
    int s = DIntr();
    B_000DE330[i] |= bits;
    if (s)
        EIntr();
}
