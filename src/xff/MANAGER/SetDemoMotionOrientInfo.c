extern void *DldSysUndefSymbol;
typedef struct { int words[3]; } DemoEntry;
typedef int Quad __attribute__((mode(TI)));
typedef struct { Quad origin; unsigned int *reference; DemoEntry *current; } DemoManager;
extern Quad ZeroPoint;
static inline char *resourceModule(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    if (offset)
        return *(char **)((char *)reference - offset);
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

DemoEntry *SetDemoMotionOrientInfo(DemoManager *manager, unsigned int *reference, const Quad *origin)
{
    if (reference) {
        manager->reference = reference;
        manager->current = resourceData(reference);
        if (resourceModule(reference) && resourceModule(reference) != DldSysUndefSymbol && resourceModule((unsigned int *)manager->current) != DldSysUndefSymbol) {
            manager->origin = *origin;
            return manager->current;
        }
    } else {
        manager->reference = 0;
        manager->current = 0;
        manager->origin = ZeroPoint;
    }
    return 0;
}
