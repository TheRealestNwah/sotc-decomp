extern unsigned char B_00183EF0[];

int _gameFlagChk(int n)
{
    return (B_00183EF0[n / 8] >> (n & 7)) & 1;
}
