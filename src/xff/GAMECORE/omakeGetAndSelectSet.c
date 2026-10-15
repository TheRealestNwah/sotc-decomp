extern unsigned char B_0018477A[];
extern void _omakeSelectFlagSet(int);

void omakeGetAndSelectSet(int i)
{
    B_0018477A[i / 8] |= 1 << (i & 7);
    _omakeSelectFlagSet(i);
}
