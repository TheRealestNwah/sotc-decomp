extern void _optionWorkSet(int, int);
extern void *getFreeModeRevControlLR(void);

static void func_000749A8(int value)
{
    _optionWorkSet(19, value);
    *(int *)getFreeModeRevControlLR() = value;
}
