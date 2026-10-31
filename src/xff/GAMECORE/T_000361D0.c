extern char *GameObject_PROTO_WALL;
extern void _SCRStartLWS(int, int, int, int);

static void T_000361D0(void)
{
    _SCRStartLWS(*(int *)(GameObject_PROTO_WALL + 8), -1, 6, 0);
}
