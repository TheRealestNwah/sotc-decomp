#ifdef NONMATCHING /* keeps motion in a1 and output/selector in s1/s2, no tail call; permuter best 755 */
extern int DldSysUndefSymbol;
extern int _AnimObjDef;
extern unsigned char RO_001183D0[];
extern void iosJumpRecoverPoint(void *, ...);
static void func_0003CF68();
static float GetMotionFloatFrameNoCaribration();

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
        iosJumpRecoverPoint(RO_001183D0, definition->name);
    return definition->animation;
}

static inline void limitCaribration(void *output, char *motion, int selector, float frame)
{
    short limit = *(short *)(motion + 4);
    if ((float)limit <= frame) {
        func_0003CF68(output, motion, limit, selector);
    } else {
        GetMotionFloatFrameNoCaribration(output, motion, selector, frame);
    }
}

void GetMotionFloatFrameWithLimitCaribration(void *output, unsigned int *h, int *selector, float frame)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        limitCaribration(output, *(char **)(animationData(resourceData(h)) + 0x20), selector[1], frame);
    }
}
#endif
