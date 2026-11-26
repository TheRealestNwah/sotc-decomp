#ifdef NONMATCHING /* 14 diffs, same size. Remaining: the Original reloads 0.0f before the second test and lays it out as bc1f/bc1t with a dead return-0 block and bc1fl; C hoists the mtc1 above the first load, so the beq slot gets a nop instead of beql's return value. */
static int func_000E1AD0(float *a, int **b)
{
    if ((*b)[1] != 2) {
        if (a[2] < 0.0f || a[2] > 0.0f || a[4] < 0.0f || a[4] > 0.0f)
            return 1;
    }
    return 0;
}
#endif
