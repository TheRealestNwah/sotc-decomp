extern char rootPtn[];
extern char *D_0017A310;
extern char *iosMallocAlign(void *, int, int);

char *CreateLoadAreaGroupData(void)
{
    char *g = iosMallocAlign(rootPtn, 0x24, 0x10);

    *(int *)(g + 0x1C) = 0;
    *(int *)(g + 0x4) = -1;
    *(int *)(g + 0x8) = -1;
    *(int *)(g + 0xC) = 0;
    *(int *)(g + 0x10) = 0;
    *(char **)(g + 0x20) = D_0017A310;
    D_0017A310 = g;
    return g;
}
