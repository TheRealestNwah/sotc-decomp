#ifdef NONMATCHING
/* 118 diffs, 9 words longer (136 vs 127). Draft from the matched siblings GetMotionColSphereInfo (dld decode, RO string) and func_0003CF68 (the body, inlined here). The Original keeps only s0-s4 across the loops; ours also saves s5-s7. Permuter (12 workers, 28 min) 2060 -> 1405 only. Not tried: separate out-pointer for the second loop only. */
typedef int s128 __attribute__((mode(TI)));
extern int DldSysUndefSymbol;
extern int _AnimObjDef;
extern unsigned char RO_001183D0[];
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
        iosJumpRecoverPoint(RO_001183D0, definition->name);
    return definition->animation;
}

static inline void *getAnimObjResource(unsigned int *reference)
{
    return *(void **)(animationData(resourceData(reference)) + 0x20);
}

typedef struct {
    int unk0;
    int unk4;
    unsigned char *unk8;
    int unkC;
    int *unk10;
    int unk14;
} AnimSrc;

extern int func_00031438(s128 *out, int a, int b, int frame);
extern int GetObjectAnimationFloatFrame(void *out, void *motion, int index, float frame, float previousFrame);
extern void GetTRS_Onake_From_ObjectAnimation(void *anim, void *s, void *t, void *r, void *q);

void GetMotionIntFrame(s128 *out, unsigned int *ref, int frame, int count)
{
    if ((int *)dldObj(ref)[2] == &_AnimObjDef) {
        AnimSrc *src = (AnimSrc *)getAnimObjResource(ref);
        int i;

        if (src->unk8 != 0) {
            if (count != src->unk14 && src->unk14 < count) {
                count = src->unk14;
            }
            for (i = 0; i < count; i++) {
                func_00031438(out + i, src->unk8[i], src->unk10[i], frame);
            }
        } else {
            struct { s128 s, t, r, q; } trs;
            char anim[0x60];

            float ff = (float)frame;

            for (i = 0; i < count; i++) {
                GetObjectAnimationFloatFrame(anim, src, i, ff, ff);
                GetTRS_Onake_From_ObjectAnimation(anim, &trs.s, &trs.t, &trs.r, &trs.q);
                out[i] = trs.t;
            }
        }
    }
}
#endif
