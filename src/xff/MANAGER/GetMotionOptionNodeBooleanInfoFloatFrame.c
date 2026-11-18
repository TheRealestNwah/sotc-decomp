extern int DldSysUndefSymbol;
extern int _AnimObjDef;
extern int _BlendMotionDef;
extern unsigned char RO_0013E670[];
extern void iosJumpRecoverPoint(void *, ...);
extern unsigned int *getBlendLastMotion(unsigned int *);
typedef struct { char a, b, c; } Bool3;
extern void func_00033B88(void *, void *, int, float, float);

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

void GetMotionOptionNodeBooleanInfoFloatFrame(Bool3 *out, unsigned int *h, int node, float f0, float f1)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        struct { char pad[0x20]; Bool3 b; char pad2[0xD]; } t __attribute__((aligned(16)));
        char *res = *(char **)(animationData(resourceData(h)) + 0x20);
        func_00033B88(&t, *(char **)(res + 0x1C) + node * 16, *(short *)(res + 4), f0, f1);
        *out = t.b;
    } else if ((int *)dldObj(h)[2] == &_BlendMotionDef) {
        GetMotionOptionNodeBooleanInfoFloatFrame(out, getBlendLastMotion(h), node, f0, f1);
    }
}
