/* parked: func_00096530 53 diffs, entrySyncAnim 12 (reg alloc), sheetMgrNopSegmentIndex 37 (lui hoist) */
#ifdef NONMATCHING
extern void *DldSysUndefSymbol;

static inline char *refModule(unsigned int *reference)
{
    unsigned int offset = *(volatile unsigned int *)reference & 0x3FFFF;

    if (offset)
        return *(char **)((char *)reference - offset);
    return 0;
}

static inline char *refModuleV(unsigned int *reference)
{
    unsigned int offset = *(volatile unsigned int *)reference & 0x3FFFF;

    if (offset)
        return *(char **)((char *)reference - offset);
    return 0;
}

static inline char *moduleData(unsigned int *reference)
{
    char *module = refModule(reference);

    if (module && module != DldSysUndefSymbol)
        return *(char **)(module + 0x10);
    return 0;
}

static inline int moduleCount(unsigned int *reference)
{
    char *module = refModule(reference);

    if (module && module != DldSysUndefSymbol)
        return *(int *)(module + 0xC);
    return 0;
}

static int func_00096530(char *self)
{
    unsigned int *ref = *(unsigned int **)(self + 8);
    unsigned int *outer = (unsigned int *)moduleData(ref);
    int count = moduleCount(ref);
    int total = count * 0x77;

    if (count > 0) {
        int i = count;
        do {
            char *e = moduleData(outer);
            int valid = 0;
            int n = moduleCount(outer);

            total += n * 0x4F;
            if (n > 0) {
                int j = n;
                do {
                    *(int *)(e + 0xC) = 0;
                    if (*(int *)(e + 0x14) >= 0) {
                        refModuleV((unsigned int *)(e + 0x68));
                        refModuleV((unsigned int *)(e + 0x6C));
                        valid++;
                    }
                    e += 0x80;
                } while (--j);
            }
            total += valid * 0x4B;
            outer += 6;
        } while (--i);
    }
    return total + 0x40;
}
#endif
