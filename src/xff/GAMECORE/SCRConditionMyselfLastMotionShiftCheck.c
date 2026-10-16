extern int DldSysUndefSymbol;
extern char *GetCharacterClass(void *);

int SCRConditionMyselfLastMotionShiftCheck(void *a, int b, int c, int d, int e, int f, int g, int i, unsigned int *h)
{
    int ret = 0;
    char *m = GetCharacterClass(a) + 0x1C0;
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    if (p == *(char **)(m + 4))
        ret = *(signed char *)(GetCharacterClass(a) + 0x360) != 0;
    return ret;
}
