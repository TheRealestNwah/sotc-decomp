int meshGetWorkSize(int count, int nodes)
{
    int size = (nodes * 64 + 16) * count;

    return (size << 1) + 0x289;
}
