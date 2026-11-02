extern int DldSysUndefSymbol;
extern char *WeaponList_HAND;
extern char *GetSCRCharaAIWorkPtr(void *);
extern void isysRequestDeleteObj(void *);
extern char *GetCharacterClass(void *);
extern void func_0007A670(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static void T_0007AA48(void *obj)
{
    char *ai = GetSCRCharaAIWorkPtr(obj);
    char *w;
    char *wl;

    if (*(int *)(ai + 0x70) != 9)
        return;
    func_0007A670(obj);
    if (*(int *)(ai + 0x78) == 0)
        return;
    w = ai + 0x60;
    if (*(void **)(w + 0x18) != 0) {
        isysRequestDeleteObj(*(void **)(w + 0x18));
        *(void **)(w + 0x18) = 0;
    }
    wl = WeaponList_HAND;
    *(char **)(GetCharacterClass(obj) + 0x111C) = dldResolve((unsigned int *)(wl + 0x14));
    *(char **)(GetCharacterClass(obj) + 0x1120) = dldResolve((unsigned int *)(wl + 0x18));
}
