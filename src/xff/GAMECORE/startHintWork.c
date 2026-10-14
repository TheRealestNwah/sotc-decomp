extern int _gameIWorkChk(int);
extern void _gameIWorkSet(int, int);

int startHintWork(void)
{
    if (_gameIWorkChk(14) == -1) {
        _gameIWorkSet(14, 0);
    }
}
