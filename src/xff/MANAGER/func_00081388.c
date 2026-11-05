extern void *DldSysUndefSymbol;

typedef struct {
    char pad0[4];
    unsigned int ref4;
    unsigned short id8;
    char padA[0x12];
    unsigned int ref1C;
    unsigned short id20;
    char pad22[0x12];
} Entry;

static inline char *refModule(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;

    if (offset)
        return *(char **)((char *)reference - offset);
    return 0;
}

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    char *module = refModule(reference);

    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static inline int resourceCount(unsigned int *reference)
{
    char *module = refModule(reference);

    if (module && module != DldSysUndefSymbol)
        return *(int *)(module + 0xC);
    return 0;
}

#ifdef NONMATCHING
/* 26 diffs: the loop counter is kept as count-1 against -1 instead of a second count check, and the id20 store branches the other way */
static void func_00081388(unsigned int *reference)
{
    int count = resourceCount(reference);
    Entry *e;
    char *r;

    if (count == 0)
        return;
    e = (Entry *)resourceData(reference);
    while (count--) {
        e->id8 = *(unsigned short *)(resourceData(&e->ref4) + 8);
        r = resourceData(&e->ref1C);
        if (r == 0)
            e->id20 = -1;
        else
            e->id20 = *(unsigned short *)(r + 8);
        e++;
    }
}
#endif
