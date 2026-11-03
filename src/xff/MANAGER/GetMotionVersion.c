#ifdef NONMATCHING /* 1 diff: target uses bne at the _BlendMotionDef check, gcc emits bnel with the default return in the delay slot */
extern int DldSysUndefSymbol;
extern int _AnimObjDef;
extern int _BlendMotionDef;
extern unsigned char RO_0013E670[];
extern void iosJumpRecoverPoint(void *, ...);
extern unsigned int *getBlendLastMotion(unsigned int *);
extern unsigned int *getBlendBaseMotion(unsigned int *);

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

int GetMotionVersion(unsigned int *h)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        return *(short *)getAnimObjResource(h);
    } else if ((int *)dldObj(h)[2] == &_BlendMotionDef) {
        return GetMotionVersion(getBlendLastMotion(h));
    }
    return -1;
}
#endif
