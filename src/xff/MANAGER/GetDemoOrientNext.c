extern void *DldSysUndefSymbol;
typedef struct { int words[3]; } DemoEntry;
typedef struct { char pad[16]; unsigned int *reference; DemoEntry *current; } DemoManager;
static inline char *resourceModule(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    if (offset)
        return *(char **)((char *)reference - offset);
    return 0;
}
static inline int resourceCount(unsigned int *reference)
{
    char *module = resourceModule(reference);
    if (module && module != DldSysUndefSymbol)
        return *(int *)(module + 0xC);
    return 0;
}
static inline DemoEntry *resourceData(unsigned int *reference)
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
        return (DemoEntry *)(data + index * *(int *)(definition + 0xC));
    }
    return 0;
}
DemoEntry *GetDemoOrientNext(DemoManager *manager)
{
    DemoEntry *current = manager->current;
    int count = resourceCount(manager->reference);
    DemoEntry *base = resourceData(manager->reference);
    if (current - base < count - 1) {
        manager->current = current + 1;
        return manager->current;
    }
    return 0;
}
