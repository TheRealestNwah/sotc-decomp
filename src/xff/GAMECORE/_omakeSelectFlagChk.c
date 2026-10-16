extern unsigned char B_00184782[];

int _omakeSelectFlagChk(int n)
{
    return (B_00184782[n / 8] >> (n & 7)) & 1;
}
