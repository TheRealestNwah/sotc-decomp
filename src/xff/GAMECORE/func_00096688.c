extern char B_0019B868[];
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void execObjectWithNonTaskSwitch(void *);

static void func_00096688(void)
{
    void **it;
    void *obj = 0;

    for (it = isysGroupForFirst(B_0019B868, 0); it != 0; it = isysGroupForNext(it, 0)) {
        obj = *it;
        execObjectWithNonTaskSwitch(obj);
    }
    if (obj != 0)
        isysGroupForExit(obj, 0);
}
