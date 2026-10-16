extern int _gameWorkChk(int);

int SCRConditionOverGameWork(void *actor, int index, int value)
{
    return _gameWorkChk(index) >= value;
}
