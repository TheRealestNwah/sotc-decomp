extern void _optionWorkSet(int, int);
extern void *getFreeModeRevControlUD(void);

static void func_000749E0(int value)
{
    _optionWorkSet(18, value);
    *(int *)getFreeModeRevControlUD() = value;
}
