typedef struct {
    const char *name;
    char pad[8];
    char *animation;
} AnimationDefinition;

extern void *DldSysUndefSymbol;
extern const char RO_0013B1F0[];
extern void iosJumpRecoverPoint(const char *, ...);

static inline AnimationDefinition *resourceData(unsigned int *reference)
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
        return (AnimationDefinition *)(data + index * *(int *)(definition + 0xC));
    }
    return 0;
}

static inline char *animationData(AnimationDefinition *definition)
{
    if (definition->animation == 0)
        iosJumpRecoverPoint(RO_0013B1F0 + 0x3480, definition->name);
    return definition->animation;
}

int getAnimObjResource(unsigned int *reference)
{
    return *(int *)(animationData(resourceData(reference)) + 0x20);
}
