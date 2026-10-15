extern int __gameMode;
extern unsigned char B_00184890[];

void gameModeSet(unsigned int m)
{
    int i = 0;
    __gameMode |= m;
    while (m != 0) {
        if (m & 1)
            B_00184890[i]++;
        m >>= 1;
        i++;
    }
}
