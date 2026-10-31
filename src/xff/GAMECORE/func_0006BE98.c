extern int _gameFlagChk(int);
extern void _gameFlagSet(int);

static void func_0006BE98(void)
{
    if (!_gameFlagChk(0x13F)) {
        _gameFlagSet(0x13F);
    }
}
