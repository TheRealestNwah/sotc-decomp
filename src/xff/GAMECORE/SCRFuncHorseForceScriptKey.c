extern int DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(void *);

void SCRFuncHorseForceScriptKey(void *a, int b, int c, int d, int e, int f, int g, int i, unsigned int *h)
{
    char *ai = GetSCRCharaAIWorkPtr(a);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    if (p != 0)
        *(long *)(ai + 0x4208) |= 1L << *(int *)(p + 4);
}
