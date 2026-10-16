extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);
extern void setPerceptionParam(void *, void *);

void SCRFuncSetPerceptionParam(void *a, int b, int c, int d, int e, int f, unsigned int *h)
{
    char *w = getSCRDataCtrlWork(a);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    setPerceptionParam(w + 0x4030, (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0);
}
