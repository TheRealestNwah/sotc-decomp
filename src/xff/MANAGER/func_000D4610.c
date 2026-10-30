extern void *iosMallocAlign(void *, int, int);

static char *func_000D4610(void *heap)
{
    char *p = iosMallocAlign(heap, 0x100, 4);
    p[0] = 0;
    return p;
}
