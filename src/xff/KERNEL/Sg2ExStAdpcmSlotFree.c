extern int B_000C5B40[];
extern void Sg2SlotFree(int);

int Sg2ExStAdpcmSlotFree(void)
{
    int n = 0;
    int i;
    for (i = 0; i < 48; i++) {
        if (B_000C5B40[i] > 0) {
            Sg2SlotFree(i);
            n++;
            B_000C5B40[i] = 0;
        }
    }
    return n;
}
