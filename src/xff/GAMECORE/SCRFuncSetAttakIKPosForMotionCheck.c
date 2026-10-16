extern int DldSysUndefSymbol;
extern char *GetCharacterClass(void *);
extern char *getSCRDataCtrlWork(void *);
extern void updateAttackWaistIKWork(void *, void *);

int SCRFuncSetAttakIKPosForMotionCheck(void *a, int b, int c, int d, int e, int f, unsigned int *h)
{
    char *m = GetCharacterClass(a) + 0x1C0;
    char *w = getSCRDataCtrlWork(a);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;

    if (p == *(char **)m)
        updateAttackWaistIKWork(a, *(void **)(*(char **)(w + 0x407C) + 0x134));
}
