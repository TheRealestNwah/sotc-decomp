extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);
extern int *GetDamageClass(void *);

int SCRConditionPlayerDamagedType(void *a, int b, int c, int d, int e, int f, int g, int i, unsigned int *h)
{
    int *dmg = GetDamageClass(*(void **)(getSCRDataCtrlWork(a) + 0x4078));

    if (*dmg == 1) {
        unsigned int v = *h;
        int off = v & 0x3FFFF;
        char *t = off != 0 ? *(char **)((char *)h - off) : 0;
        char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
        if (p == (char *)dmg[0x14])
            return 1;
    }
    return 0;
}
