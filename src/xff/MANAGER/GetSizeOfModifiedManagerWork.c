int GetSizeOfModifiedManagerWork(int n)
{
    int w;
    if (n == 0)
        return 0;
    if (n <= 0xFFFF)
        w = n >= 0x100 ? 2 : 1;
    else
        w = 4;
    return ((n + 15) & ~15) + ((w * n + 15) & ~15);
}
