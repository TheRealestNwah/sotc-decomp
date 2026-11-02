extern void iosFree(void *);

static void func_000F2A40(int *a)
{
    a[0] = 0;
    if (a[1] != 0) {
        iosFree((void *)a[1]);
        a[1] = 0;
    }
}
