extern int widePathCollisionDirect(void *, void *, void *, float, int, int, int);

static int func_000FACE0(char *p, void *a, void *b)
{
    return widePathCollisionDirect(p, a, b, *(float *)(p + 0x3C3C), *(int *)(p + 0x3C40),
                                   *(int *)(p + 0xF0), 0) != 0;
}
