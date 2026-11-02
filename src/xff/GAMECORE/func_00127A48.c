static int func_00127A48(int n, char *a)
{
    int i;
    int v = *(int *)(a + 0x14);

    for (i = 0; i != n; i++) {
        if (v < 0)
            return -2;
        if (v > 0 && (v & 0x10000))
            v = *(int *)(*(char **)(*(char **)(a + 0x10) + 0x24) + (v & ~0x10000) * 64 + 0x30);
        else
            v = *(int *)(*(char **)(*(char **)(a + 0x10) + 0x8) + v * 64 + 0x38);
    }
    return v;
}
