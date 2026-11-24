/* Parked: 20 diffs. The Original keeps the stretch word and its >>20 apart in the unsigned-to-float conversion (srl 1 on the shifted value) and reloads the animation pointer after the recover check without a branch-likely. */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern int _AnimObjDef;
extern int _BlendMotionDef;
extern unsigned char RO_0013E670[];
extern void iosJumpRecoverPoint(void *, ...);

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

static inline char *resourceData2(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol) {
        return *(char **)(module + 0x10) + ((*reference >> 18) & 0xFFF) * *(int *)(*(char **)(module + 8) + 0xC);
    }
    return 0;
}

static inline unsigned int *blendBaseMotion(unsigned int *reference)
{
    return (unsigned int *)(resourceData2((unsigned int *)resourceData(reference)) + 0x50);
}

float GetMotionStretchRatio(unsigned int *h)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        char *motion = getAnimObjResource(h);
        float r = 1.0f;
        unsigned int s = *(unsigned int *)(motion + 4) >> 20;
        if (s != 0) {
            r = (float)s * (1.0f / 4096.0f);
        }
        return r;
    } else if ((int *)dldObj(h)[2] == &_BlendMotionDef) {
        return GetMotionStretchRatio(blendBaseMotion(h));
    }
    return 0.0f;
}
#endif
