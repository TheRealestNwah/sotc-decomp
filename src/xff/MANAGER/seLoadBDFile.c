extern void *DldSysUndefSymbol;
extern char *sheetFileGetDataAdrs(void *);
static void func_000DCEF0(void *, void *, int, void *, int, int);

static inline void *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

void seLoadBDFile(void *sheet, int unused, int dest)
{
    char *adrs = sheetFileGetDataAdrs(sheet);

    func_000DCEF0(adrs, resourceData((unsigned int *)(adrs + 0x18)), dest, sheet, 0, 0);
}
