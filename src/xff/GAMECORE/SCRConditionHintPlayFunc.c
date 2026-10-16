extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);
extern int _gameIWorkChk(int);

int SCRConditionHintPlayFunc(void *a, int b, int c, int d, int e, int f, int g, int i, unsigned int *h)
{
    int *hint = (int *)(getSCRDataCtrlWork(a) + 0x40E0);
unsigned int v = *h;
int voff = v & 0x3FFFF;
char *t = voff != 0 ? *(char **)((char *)h - voff) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;

    if (hint[0] != 0 && _gameIWorkChk(14) != -1 && _gameIWorkChk(14) < hint[1] && p == (char *)hint[0] + _gameIWorkChk(14) * 28 && hint[4] != 0)
        return 1;
    return 0;
}
