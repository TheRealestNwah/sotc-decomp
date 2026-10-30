extern int _optionWorkChk(int);
extern void _optionWorkSet(int, int);
extern int *getBrightness(void);

static int func_00074708(void)
{
    return _optionWorkChk(1);
}

static int T_00074720(void)
{
    return _optionWorkChk(4);
}

static int T_00074738(void)
{
    return _optionWorkChk(5);
}

static int T_00074750(void)
{
    return _optionWorkChk(2);
}

static int T_00074768(void)
{
    return _optionWorkChk(6);
}

static int T_00074780(void)
{
    return _optionWorkChk(17);
}

static int T_00074798(void)
{
    return _optionWorkChk(22);
}

static int T_000747B0(void)
{
    return _optionWorkChk(21);
}

static int T_000747C8(void)
{
    return _optionWorkChk(19);
}

static int T_000747E0(void)
{
    return _optionWorkChk(18);
}

static int T_000747F8(void)
{
    return _optionWorkChk(20);
}

static void T_00074810(int v)
{
    _optionWorkSet(1, v);
    *getBrightness() = v;
}
