extern int B_00151840;
extern void **D_00139F10;
extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
extern void *memset(void *, int, unsigned int);
extern void *func_000E21D0(int, void *);

static void func_000E4800(void *data, int index, int count)
{
    B_00151840 = count + 1;
    D_00139F10 = iosMallocAlign(rootPtn, B_00151840 * 4, 16);
    memset(D_00139F10, 0, B_00151840 * 4);
    D_00139F10[index] = func_000E21D0(index, data);
}
