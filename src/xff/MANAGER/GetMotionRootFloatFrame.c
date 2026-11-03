#ifdef NONMATCHING /* 14 diffs: animation pointer held in a1 instead of reloaded into v0, and &v1 kept in s0 across the second call */
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

typedef int s128 __attribute__((mode(TI)));
typedef union Vector {
    s128 quad;
    float v[4];
} Vector;
extern int func_00031DB8(Vector *, void *, int);

static inline void lerpVec(Vector *out, Vector *a, Vector *b, float t)
{
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%3)\n"
                         ".set reorder\n"
                         : : "f"(t), "r"(a), "r"(b), "r"(out) : "memory", "$8");
}

int GetMotionRootFloatFrame(Vector *out, unsigned int *h, float frame)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        AnimationDefinition *def = resourceData(h);
        int i, next;
        void *res;
        Vector v0, v1;
        if (def->animation == 0)
            iosJumpRecoverPoint(RO_0013E670, def->name);
        i = (int)frame;
        res = *(void **)(def->animation + 0x20);
        next = i + 1;
        frame -= (float)i;
        if (frame == 0.0f) {
            func_00031DB8(out, res, i);
        } else {
            func_00031DB8(&v0, res, i);
            func_00031DB8(&v1, res, next);
            lerpVec(out, &v1, &v0, frame);
        }
        out->v[3] = 1.0f;
    } else if ((int *)dldObj(h)[2] == &_BlendMotionDef) {
        GetMotionRootFloatFrame(out, getBlendBaseMotion(h), frame);
    }
}
#endif
