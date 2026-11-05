extern int func_000781E0(void *);
extern int ModelDispGetWorkSize(int);

#ifdef NONMATCHING
/* 71 diffs: flag-size sum uses xori/movn chains and register order the original lays out differently */
int func_00074270(char *w) {
    int n = *(int *)(w + 4);
    int hasExtra = 0;
    int flags;
    int unit;
    int size;
    int base;
    int total;

    if (*(int *)(w + 0x78) != 0 || *(int *)(w + 0xC) != 0 || *(int *)(w + 0x10) != 0 ||
        *(void **)(w + 8) != 0)
        hasExtra = 1;
    flags = *(int *)(w + 0x3C);
    unit = n << 6;
    size = 0;
    if (flags & 2)
        size += unit;
    if (flags & 4)
        size += unit;
    if (flags & 0x10)
        size += unit;
    if (flags & 0x20)
        size += unit;
    if (flags & 8)
        size += unit;
    if (flags & 0x40)
        size += unit;
    if (flags & 0x80)
        size += unit;
    if (flags & 1)
        size += n * 16;
    base = (hasExtra ? 0x123 : 0) + size;
    total = base + 0x33;
    if (*(int *)(w + 0x38) != 0 || *(int *)(w + 0xC) != 0)
        total = base + 0xF6;
    if (func_000781E0(w) == 1)
        total += 0x43;
    if (*(char **)(w + 8) != 0)
        total += (n * 4 + (n >> 6)) * 32 + 0x73 + ModelDispGetWorkSize(*(int *)(*(char **)(w + 8) + 0x20));
    return total;
}
#endif
