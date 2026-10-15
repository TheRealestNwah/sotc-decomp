typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern void *iosMallocAlign(Ptn *, int, int);
extern void *iosMallocAlignNoCheck(Ptn *, int, int);

void *malloc_from_src_partition(Ptn *ptn, int size, int unused, int fallback)
{
    void *p = 0;
    if (ptn != 0)
        p = iosMallocAlignNoCheck(ptn, size, 16);
    if (p == 0 && fallback == 1)
        p = iosMallocAlign(&rootPtn, size, 16);
    return p;
}
