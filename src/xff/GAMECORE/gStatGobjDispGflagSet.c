extern void _gameFlagSet(int);
extern void _gameFlagCls(int);

void gStatGobjDispGflagSet(int *g)
{
    int f = g[2];
    if (f != 0) {
        if (!((unsigned int)g[4] >> 1 & 1))
            _gameFlagSet(f);
        else
            _gameFlagCls(f);
    }
}
