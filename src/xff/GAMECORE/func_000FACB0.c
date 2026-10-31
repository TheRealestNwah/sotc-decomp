extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, void *, int, int, void *, int);

static int func_000FACB0(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1)
{
    int r = 0;
    if (a3)
        r = ClipCollisionDirectCallBack(a0, a1, a2, a3, t0, 0, 0, t1, 0);
    return r;
}
