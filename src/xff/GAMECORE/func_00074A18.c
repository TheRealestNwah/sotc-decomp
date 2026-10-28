extern void _optionWorkSet(int, int);
extern void *getFreeModeRevAngleVelRatio(void);

static void func_00074A18(int value)
{
    _optionWorkSet(20, value);
    *(int *)getFreeModeRevAngleVelRatio() = value;
}
