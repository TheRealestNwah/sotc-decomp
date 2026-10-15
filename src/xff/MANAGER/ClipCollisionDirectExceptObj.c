extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, void *, int, int, int, void *);
extern int func_000B6AE0();

int ClipCollisionDirectExceptObj(void *a, void *b, void *c, void *d, void *e)
{
    return ClipCollisionDirectCallBack(a, b, c, d, func_000B6AE0, 0, 0, 0, e);
}
