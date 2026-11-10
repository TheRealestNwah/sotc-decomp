/* Parked: 1 diff (branch-likely `bnel` where the original has `bne` with the result=0 slot). */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern int _AnimObjDef;
extern int _BlendMotionDef;
extern unsigned char RO_0013E670[];
extern void iosJumpRecoverPoint(void *, ...);
extern unsigned int *getBlendLastMotion(unsigned int *);

typedef struct {
    const char *name;
    char pad[8];
    char *animation;
} AnimationDefinition;

static inline int *dldObj(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t : 0;
}

static inline AnimationDefinition *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol) {
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
        iosJumpRecoverPoint(RO_0013E670, definition->name);
    return definition->animation;
}

static inline void *getAnimObjResource(unsigned int *reference)
{
    return *(void **)(animationData(resourceData(reference)) + 0x20);
}

void *GetAnimObjResource(unsigned int *h)
{
    AnimationDefinition *def;
    void *result;
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        def = resourceData(h);
    } else if (result = 0, (int *)dldObj(h)[2] == &_BlendMotionDef) {
        def = resourceData(getBlendLastMotion(h));
    } else {
        return result;
    }
    if (*(char * volatile *)&def->animation == 0)
        iosJumpRecoverPoint(RO_0013E670, def->name);
    result = *(void **)(def->animation + 0x20);
    return result;
}
#endif
