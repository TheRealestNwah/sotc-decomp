extern void _optionWorkSet(int, int);
extern int setSoundMode(int);

static int T_00074A68(int mode)
{
    _optionWorkSet(3, mode);
    return setSoundMode(mode);
}
