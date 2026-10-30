extern void *memset(void *, int, unsigned int);
static void func_000ECDB0(void *dst, float *buf, int n, float v)
{
    int i;
    memset(dst, 0, n * 4);
    for (i = 0; i < n; i++)
        buf[i] = v;
}
