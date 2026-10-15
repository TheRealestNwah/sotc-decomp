extern unsigned char B_0018477A[];

void _omakeGetFlagCls(int i)
{
    B_0018477A[i / 8] &= ~(1 << (i & 7));
}
