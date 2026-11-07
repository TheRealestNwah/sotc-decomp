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

static inline int physicalIdDirect(char *res, int id)
{
    int n = *(int *)(res + 0x18);
    unsigned char *p = *(unsigned char **)(res + 0x28);
    int i;
    for (i = 0; i < n; i++) {
        if (*p++ == id)
            return i;
    }
    return -1;
}

static inline void *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    unsigned int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != (int *)DldSysUndefSymbol)
        return (void *)(t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3]);
    return 0;
}

static inline char *dldEntry(char *handle)
{
    unsigned int encoded = *(unsigned int *)handle;
    int offset = encoded & 0x3FFFF;
    char *table = offset != 0 ? *(char **)(handle - offset) : 0;
    return (table != 0 && table != (char *)DldSysUndefSymbol)
        ? *(char **)(table + 0x10) + (((*(unsigned int *)handle >> 18) & 0xFFF)) * *(int *)(*(char **)(table + 8) + 0xC) : 0;
}

char *getBlendBaseMotion(char *handle)
{
    char *first = dldEntry(handle);
    char *entry = first;
    char *motion;
    while ((motion = dldEntry(entry)) != 0) {
        if (*(int *)(entry + 8) & 1)
            return motion + 0x50;
        entry += 12;
    }
    return dldEntry(first) + 0x50;
}

char *getBlendLastMotion(char *handle)
{
    char *entry = dldEntry(handle);
    for (;;) { if (dldEntry(entry + 12) != 0) entry += 12; else break; }
    return dldEntry(entry) + 0x50;
}

char *DebugGetAnimObjName(unsigned int *h)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef)
        return *(char **)dldElem(h);
    if ((int *)dldObj(h)[2] == &_BlendMotionDef)
        return *(char **)dldElem((unsigned int *)getBlendLastMotion((char *)h));
    return 0;
}

int GetMotionNbOptionNodes(unsigned int *h)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        return *(int *)((char *)getAnimObjResource(h) + 0x18);
    } else if ((int *)dldObj(h)[2] == &_BlendMotionDef) {
        return GetMotionNbOptionNodes((unsigned int *)getBlendLastMotion((char *)h));
    }
    return -1;
}

int GetMotionOptionNodePhysicalId(unsigned int *h, int id)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        return physicalIdDirect(getAnimObjResource(h), id);
    } else if ((int *)dldObj(h)[2] == &_BlendMotionDef) {
        return GetMotionOptionNodePhysicalId((unsigned int *)getBlendLastMotion((char *)h), id);
    }
    return -1;
}

int GetMotionVersion(unsigned int *h)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        return *(short *)getAnimObjResource(h);
    } else if ((int *)dldObj(h)[2] == &_BlendMotionDef) {
        return GetMotionVersion((unsigned int *)getBlendLastMotion((char *)h));
    }
    return -1;
}

int GetMotionResourceOriginalFrames(unsigned int *h)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        return ((short *)getAnimObjResource(h))[2];
    } else if ((int *)dldObj(h)[2] == &_BlendMotionDef) {
        return GetMotionResourceOriginalFrames((unsigned int *)getBlendBaseMotion((char *)h));
    }
    return 0;
}
