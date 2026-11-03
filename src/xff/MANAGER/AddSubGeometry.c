extern void *DldSysUndefSymbol;
extern int func_00048F90(int, int, int, char **, int, int, int, char *, char *, int, int, int, int);

static inline char *resourceData(unsigned int *reference)
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

int AddSubGeometry(int a, int b, int c, char **d, int e, int f, int g, int h, int i, int j, int k)
{
    char *p = *d;
    char *res;
    char *tmp;

    if (p) {
        tmp = resourceData((unsigned int *)(p + 0x28));
        res = tmp;
    } else
        res = 0;
    return func_00048F90(a, b, c, d, e, f, g, p, res, h, i, j, k);
}
