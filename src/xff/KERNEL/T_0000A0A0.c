extern void *B_000543A0;
extern void *iosMallocAlign(void *, int, int);

static void *T_0000A0A0(int size)
{
    return iosMallocAlign(B_000543A0, size, 16);
}
