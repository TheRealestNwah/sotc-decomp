extern void *iosMallocAlign(void *, int, int);

void InitStrHash(int *hash, void *partition, int size)
{
    int bits = -2;
    int i;

    while (size != 0) {
        size >>= 1;
        ++bits;
    }
    if (bits < 0)
        bits = 0;
    hash[0] = 1 << bits;
    hash[1] = (int)iosMallocAlign(partition, hash[0] * 4, 16);
    for (i = 0; i < hash[0]; ++i)
        ((int *)hash[1])[i] = 0;
}

