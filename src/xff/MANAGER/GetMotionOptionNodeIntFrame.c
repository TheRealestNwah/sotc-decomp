#ifdef NONMATCHING
/* ~77 diffs, 10 words longer (161 vs 151). Sibling of GetMotionIntFrame / GetMotionOptionNodeFloatFrame: decodes the dld ref, checks _AnimObjDef, gets the animation resource (RO_001183D0 recover string when missing), indexes the option-node table at +0x1C by node (stride 16), fills the 3-float vector (flag 0: raw floats, 2: s16 compressed with scale p[1,3,5] * 2^-15 + base p[0,2,4], else frame-indexed floats; w = 1.0f), then runs func_00031438 / func_00032B78 on the two optional tracks. The Original loads each s16 right before its multiply (lh/cvt/mul/mul/add per component) and keeps the table entry in $s0 with the vector pointer in $s1; ours hoists the three lh loads and uses lb for the flag where the original uses lbu. */
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


extern void func_00031438(void *, int, void *, int);
extern void func_00032B78(void *, int, void *, int);

void GetMotionOptionNodeIntFrame(void *a0, float *out, void *a2, unsigned int *ref, int node, int frame)
{
    if ((int *)dldObj(ref)[2] == &_AnimObjDef) {
        unsigned char *e = *(unsigned char **)((char *)getAnimObjResource(ref) + 0x1C) + node * 16;
        float *p = *(float **)(e + 4);

        if (p != 0) {
            out[3] = 1.0f;
            if (e[2] == 0) {
                out[0] = p[0];
                out[1] = p[1];
                out[2] = p[2];
            } else if (e[2] == 2) {
                short *h = *(short **)((char *)p + 0x18) + frame * 3;

                out[0] = (float)h[0] * p[1] * 3.0517880e-05f + p[0];
                out[1] = (float)h[1] * p[3] * 3.0517880e-05f + p[2];
                out[2] = (float)h[2] * p[5] * 3.0517880e-05f + p[4];
            } else {
                float *q = p + frame * 3;

                out[0] = q[0];
                out[1] = q[1];
                out[2] = q[2];
            }
        }
        if (*(void **)(e + 8) != 0)
            func_00031438(a0, *(unsigned char *)(e + 1), *(void **)(e + 8), frame);
        if (*(void **)(e + 0xC) != 0)
            func_00032B78(a2, *(unsigned char *)(e + 0), *(void **)(e + 0xC), frame);
    }
}
#endif
