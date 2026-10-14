extern unsigned char B_00183EF0[];

void _gameFlagSet(int i)
{
    B_00183EF0[i / 8] |= 1 << (i & 7);
}
