extern void _gameWorkSet(int, int);

void SCRFuncSetGameWork(void *context, int index, int value)
{
    _gameWorkSet(index, value);
}
