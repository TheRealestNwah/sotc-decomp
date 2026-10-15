extern int _gameFlagChk(int);

int gStatGobjDispGflagChk(int *g)
{
    int f = g[2];
    if (f == 0)
        return 0;
    if (!((unsigned int)g[4] >> 1 & 1))
        return _gameFlagChk(f);
    return _gameFlagChk(f) == 0;
}
