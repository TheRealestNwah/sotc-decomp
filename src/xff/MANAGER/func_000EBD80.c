extern void *memset(void *, int, unsigned int);

static void func_000EBD80(int *p)
{
    *p = 0;
    memset(p + 4, 0x7E, 0x40);
}
