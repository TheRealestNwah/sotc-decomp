extern void *DldSysUndefSymbol;
extern int strcmp(const char *, const char *);
typedef struct { int unknown; const char *name; } WaterEffectDefinition;
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
static inline WaterEffectDefinition *resourceEntries(unsigned int *reference)
{
    char *module = resourceModule(reference);
    if (module && module != DldSysUndefSymbol)
        return *(WaterEffectDefinition **)(module + 0x10);
    return 0;
}
static inline WaterEffectDefinition *findDefinition(WaterEffectDefinition *entry, int count, const char *name)
{
    int index;
    for (index = 0; index < count; ++index, ++entry) {
        if (strcmp(entry->name, name) == 0)
            return entry;
    }
    return 0;
}
static inline WaterEffectDefinition *lookupDefinition(unsigned int *reference, int count, const char *name)
{
    if (count) {
        WaterEffectDefinition *entry = resourceEntries(reference);
        return findDefinition(entry, count, name);
    }
    return 0;
}
WaterEffectDefinition *GetCollisionDetectEffectWaterOnlyDefByName(unsigned int *reference, const char *name)
{
    int count = resourceCount(reference);
    return lookupDefinition(reference, count, name);
}
