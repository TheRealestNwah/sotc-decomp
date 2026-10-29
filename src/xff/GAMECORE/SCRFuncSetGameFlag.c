extern void _gameFlagSet(int);

void SCRFuncSetGameFlag(void *context, int flag)
{
    _gameFlagSet(flag);
}
