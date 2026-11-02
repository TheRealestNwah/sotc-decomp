extern int D_0017A3AC;
extern char *GetLayoutClass(void *);
extern void _isysDeleteGroup(void *, void *, int);
extern void iosMallocSetExecGarbageCallback(int, int, int);
extern void isysRequestDeleteObj(void *);

static void func_00024BA8(void *obj)
{
    char *l = GetLayoutClass(obj);
    char *s = **(char ***)(l + 0x144);

    _isysDeleteGroup(s, &D_0017A3AC, 0);
    *(long *)(*(char **)(l + 0x144) + 0x260) |= 0x10;
    iosMallocSetExecGarbageCallback(*(long *)(s + 0x1C), -1, 0);
    isysRequestDeleteObj(s);
    isysRequestDeleteObj(obj);
}
