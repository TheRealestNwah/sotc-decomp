extern void *memset(void *, int, unsigned int);

static void func_0000DAF0(int *p)
{
    *p = 0;
    memset(p + 1, 0, 0x28);
}
