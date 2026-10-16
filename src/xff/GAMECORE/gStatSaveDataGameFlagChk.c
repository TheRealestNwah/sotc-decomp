extern unsigned char B_001848B0[];

int gStatSaveDataGameFlagChk(int n)
{
    return (B_001848B0[n / 8] >> (n & 7)) & 1;
}
