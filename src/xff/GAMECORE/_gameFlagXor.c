extern unsigned char B_00183EF0[];

int _gameFlagXor(int i)
{
    unsigned char *p = &B_00183EF0[i / 8];
    *p ^= 1 << (i & 7);
    return (*p >> (i & 7)) & 1;
}
