extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);

int SCRConditionSpecifiedModeByMySelf(void *a, int b, int c, int d, int e, int f, int g, int i, unsigned int *h)
{
    char *w = getSCRDataCtrlWork(a);
    unsigned int v;
    int off;
    char *t;
    char *p;

    if (*(int *)(w + 0x4094) != 0) {
        v = *h;
        off = v & 0x3FFFF;
        t = off != 0 ? *(char **)((char *)h - off) : 0;
        p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
        if (p == *(char **)(w + 0x4098))
            return 1;
    }
    return 0;
}
