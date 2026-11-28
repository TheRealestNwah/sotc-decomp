extern void *DldSysUndefSymbol;
extern int D_0017A86C, D_0017A874;

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module != 0 && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static inline int dldField(unsigned int *reference, int off)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module != 0 && module != DldSysUndefSymbol)
        return *(int *)(module + off);
    return 0;
}

#ifdef NONMATCHING /* 25 diffs, same word count: register numbering only. The Original keeps the record iterator in $t0 and the D_0017A874 column load in $a1, where ours uses $a3 and $a0. */
static int func_000281F0(int key, unsigned int *ref)
{
    unsigned int *it;
    char *base;
    int n, i;
    char *want;
    unsigned int *entry;
    int idx;

    { register unsigned int *r __asm__("$2") = (unsigned int *)dldField(ref, 0x10); it = r; }
    if (it == 0)
        return 0;
    n = dldField(ref, 0xC);
    { char *row = (char *)D_0017A86C + ((key >> 5) & 0x3FF) * 0x9C; entry = (unsigned int *)(D_0017A874 * 4 + row + 8); }
    base = resourceData(entry);
    idx = (key << 27) >> 27;
    want = base + idx * 0x3C;
    i = n - 1;
    if (n != 0) {
        do {
            if (resourceData(it) == want)
                return 1;
            it++;
        } while (--i != -1);
    }
    return 0;
}
#endif
