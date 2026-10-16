extern unsigned char B_0018477A[];

int _omakeGetFlagChk(int n)
{
    return (B_0018477A[n / 8] >> (n & 7)) & 1;
}
