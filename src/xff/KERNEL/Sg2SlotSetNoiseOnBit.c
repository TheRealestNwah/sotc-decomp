extern int B_000DE340[];
extern int DIntr(void);
extern int EIntr(void);

void Sg2SlotSetNoiseOnBit(int i, int bits)
{
    int s = DIntr();
    B_000DE340[i] |= bits;
    if (s)
        EIntr();
}
