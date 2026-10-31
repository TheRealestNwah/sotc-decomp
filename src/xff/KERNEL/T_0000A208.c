extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
extern int D_00040900;

static void *T_0000A208(int size, int align)
{
    void *r = iosMallocAlign(rootPtn, size, align);

    D_00040900 += size;
    return r;
}
