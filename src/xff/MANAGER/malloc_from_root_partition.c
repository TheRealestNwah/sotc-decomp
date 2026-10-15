typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern void *iosMallocAlign(Ptn *, int, int);

void *malloc_from_root_partition(int size)
{
    void *p = iosMallocAlign(&rootPtn, size, 16);
    size = 0;
    return p;
}
