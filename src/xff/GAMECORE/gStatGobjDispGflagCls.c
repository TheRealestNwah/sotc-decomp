typedef struct { int a, b, flag; int c; unsigned int x : 1; unsigned int cls : 1; } Gobj;
extern void _gameFlagSet(int);
extern void _gameFlagCls(int);

void gStatGobjDispGflagCls(Gobj *g)
{
    if (g->flag != 0) {
        if (g->cls == 1)
            _gameFlagSet(g->flag);
        else
            _gameFlagCls(g->flag);
    }
}
