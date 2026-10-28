extern void _optionWorkSet(int, int);
extern void *getScreenOffsetX(void);

static void func_00074848(int value)
{
    _optionWorkSet(4, value);
    *(int *)getScreenOffsetX() = value;
}
