extern void *B_000543A0;
extern void *iosMallocAlign(void *, int, int);

static void *func_0000A078(int size, int align)
{
    return iosMallocAlign(B_000543A0, size, align);
}
