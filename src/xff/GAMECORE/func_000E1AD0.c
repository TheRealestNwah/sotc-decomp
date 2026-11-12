#ifdef NONMATCHING /* 14 diffs: branch-likely/delay-slot layout of the nonzero tests, mtc1 zero hoisting */
static int func_000E1AD0(float *a, int **b)
{
    register int *p __asm__("$2") = *b;
    register int t __asm__("$3") = p[1];
    if (t == 2)
        return 0;
    return a[2] < 0.0f || a[2] > 0.0f || a[4] < 0.0f || a[4] > 0.0f;
}
#endif
