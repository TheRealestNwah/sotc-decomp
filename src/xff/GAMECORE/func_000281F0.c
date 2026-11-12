extern void *DldSysUndefSymbol;
extern int D_0017A86C, D_0017A874;

static inline char *dldBase(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module == 0 || module == DldSysUndefSymbol)
        return 0;
    return module;
}

static inline char *resourceData(unsigned int *reference)
{
    char *module = dldBase(reference);
    if (module) {
        int index = (*reference >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

#ifdef NONMATCHING /* 99 diffs, same word count: dld lookups should branch on the module before loading its field (delay-slot form), saved a2/a3 numbering */
static int func_000281F0(unsigned int key, unsigned int *ref)
{
    char *mod = dldBase(ref);
    unsigned int *it;
    char *base;
    int n, i;
    char *want;
    unsigned int *entry;
    int idx;

    it = 0;
    if (mod)
        it = *(unsigned int **)(mod + 0x10);
    if (it == 0)
        return 0;
    mod = dldBase(ref);
    n = 0;
    if (mod)
        n = *(int *)(mod + 0xC);
    entry = (unsigned int *)((char *)D_0017A86C + ((key >> 5) & 0x3FF) * 0x9C + D_0017A874 * 4 + 8);
    base = resourceData(entry);
    idx = ((int)(key << 27)) >> 27;
    want = base + idx * 0x3C;
    i = n - 1;
    if (n != 0) {
        do {
            if (resourceData(it++) == want)
                return 1;
        } while (--i != -1);
    }
    return 0;
}
#endif
