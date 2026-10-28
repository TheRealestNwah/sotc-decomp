extern int B_000DE350[];
extern int DIntr(void);
extern int EIntr(void);

void Sg2SlotSetReverbOnBit(int i, int bits)
{
    int s = DIntr();
    B_000DE350[i] |= bits;
    if (s)
        EIntr();
}
