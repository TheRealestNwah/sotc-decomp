extern void *DldSysUndefSymbol;
extern int strcmp(const char *, const char *);
typedef struct { const char *name; char rest[40]; } DamageDefinition;
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
static inline DamageDefinition *resourceEntries(unsigned int *reference)
{
    char *module = resourceModule(reference);
    if (module && module != DldSysUndefSymbol)
        return *(DamageDefinition **)(module + 0x10);
    return 0;
}
static inline DamageDefinition *findDefinition(DamageDefinition *entry, int count, const char *name)
{
    int remaining;
    for (remaining = count - 1; remaining != -1; --remaining, ++entry) {
        if (strcmp(entry->name, name) == 0)
            return entry;
    }
    return 0;
}
DamageDefinition *GetDamageDefByName(unsigned int *reference, const char *name)
{
    int count = resourceCount(reference);
    DamageDefinition *entry = resourceEntries(reference);
    return findDefinition(entry, count, name);
}
