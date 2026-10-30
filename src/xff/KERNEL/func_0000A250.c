typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern void *iosMallocAlign(Ptn *, int, int);
extern int D_00040900;

static void *func_0000A250(int size)
{
    void *p = iosMallocAlign(&rootPtn, size, 0x40);
    D_00040900 += size;
    return p;
}
