extern void _optionWorkSet(int, int);
extern void setAspect(int);
extern void *getSightOnRevCntrlLR(void);

static void func_000748B8(int v)
{
    _optionWorkSet(2, v);
    setAspect(v);
}

static void T_000748E8(int v)
{
    _optionWorkSet(6, v);
    setAspect(v);
}

static void T_00074918(int v)
{
    _optionWorkSet(0x11, v);
}

static void T_00074938(int v)
{
    _optionWorkSet(0x16, v);
    *(int *)getSightOnRevCntrlLR() = v;
}
