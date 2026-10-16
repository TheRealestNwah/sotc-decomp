int GetClothWorkSize(char *c)
{
    int n = 0;
    char *p = c;
    int size;
    int i;

    while (*(short *)p >= 0) {
        p += 0x34;
        n++;
    }
    size = n * 0xC3 + 0x4B;
    for (i = 0; i < n; i++) {
        size = size + (*(int *)(c + 4) * 24 + *(int *)(c + 4) * *(int *)(c + 8) * 64) + 0x33;
        c += 0x34;
    }
    return size;
}
