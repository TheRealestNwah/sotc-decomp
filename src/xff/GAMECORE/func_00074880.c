extern void _optionWorkSet(int, int);
extern void *getScreenOffsetY(void);

static void func_00074880(int value)
{
    _optionWorkSet(5, value);
    *(int *)getScreenOffsetY() = value;
}
