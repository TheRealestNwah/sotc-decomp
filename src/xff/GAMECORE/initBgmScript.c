extern int B_001887C8;

void initBgmScript(void)
{
    long mask = 0x1800000000000000;

    B_001887C8 = 0;
    do {
        mask >>= 1;
        B_001887C8++;
    } while (!(mask & 1));
}
