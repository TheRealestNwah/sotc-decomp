extern void _optionWorkSet(int, int);
extern void *getSightOnRevCntrlUD(void);

static void func_00074970(int value)
{
    _optionWorkSet(21, value);
    *(int *)getSightOnRevCntrlUD() = value;
}
