extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);
extern char *GetCharacterClass(void *);

int SCRConditionPlayerMotionCheck(void *a, int b, int c, int d, int e, int f, int g, int i, unsigned int *h)
{
    char *w = GetCharacterClass(*(void **)(getSCRDataCtrlWork(a) + 0x4078)) + 0x1C0;
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    return p == *(char **)w;
}
