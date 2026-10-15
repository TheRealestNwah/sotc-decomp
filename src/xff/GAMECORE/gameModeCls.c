extern signed char B_00184890[];
extern unsigned int __gameMode;

void gameModeCls(unsigned int mask)
{
    int i = 0;
    while (mask != 0) {
        if (mask & 1) {
            if (--B_00184890[i] == 0)
                __gameMode &= ~(1 << i);
            else if (B_00184890[i] < 0)
                B_00184890[i] = 0;
        }
        mask >>= 1;
        i++;
    }
}
