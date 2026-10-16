extern void *D_00130340;
extern char rootPtn[];
extern void *iosMallocAlignNoCheck(void *, int, int);
extern void *iosMallocAlign(void *, int, int);

void *malloc_from_fast_get_partition(int size, int unused, int fallback)
{
    void *p = 0;

    if (D_00130340 != 0)
        p = iosMallocAlignNoCheck(D_00130340, size, 0x10);
    if (p == 0 && fallback == 1)
        p = iosMallocAlign(rootPtn, size, 0x10);
    return p;
}
