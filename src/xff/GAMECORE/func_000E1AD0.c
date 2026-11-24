#ifdef NONMATCHING /* 19 diffs, same size (29 words). Remaining: the first test's bc1t targets the second bc1t instead of the return, and the second test is laid out as bc1f/bc1t with the dead return-0 block and bc1fl; C builds the result in v1 and keeps the beql slot. */
static inline int nz(float f)
{
    int r = 0;
    if (f < 0.0f || f > 0.0f)
        r = 1;
    return r;
}

static int func_000E1AD0(float *a, int **b)
{
    register int *p __asm__("$2") = *b;
    register int t __asm__("$3") = p[1];
    if (t == 2)
        return 0;
    return nz(a[2]) || nz(a[4]);
}
#endif
