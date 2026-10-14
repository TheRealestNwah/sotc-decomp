extern int _gameFlagSet();

int SCRFuncSetGameFlag(int a, int b, int c, int d)
{
    return _gameFlagSet(b, b, c, d);
}
