/* Parked: 117 diffs. Original keeps the header word in a3 (not s1), selector in s1 and output in s2; tail-calls the clamp helper. */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern int _AnimObjDef;
extern int _BlendMotionDef;
extern unsigned char RO_0013E670[];
extern void iosJumpRecoverPoint(void *, ...);
extern void func_00039858();
extern void GetMotionFloatFrameNoCaribration();

typedef struct {
    const char *name;
    char pad[8];
    char *animation;
} AnimationDefinition;

static inline int *dldObj(unsigned int *h, unsigned int enc)
{
    unsigned int off = enc & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t : 0;
}

static inline char *dldEntry(unsigned int *reference, unsigned int encoded)
{
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
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

typedef struct { char pad[4]; short frameCount; } Motion;
static inline void getMotionFloatFrame(void *output, Motion *motion, int selector, float frame)
{
    float original = frame;
    if (motion->frameCount == 1) {
        int integer = (int)frame;
        frame -= (float)integer;
    } else {
        int last = motion->frameCount - 1;
        frame -= (float)(last * (int)(frame / (float)last));
    }
    if (frame == 0.0f && original > 0.0f)
        frame = (float)(motion->frameCount - 1);
    GetMotionFloatFrameNoCaribration(output, motion, selector, frame);
}

void GetMotionFloatFrame(void *output, unsigned int *h, int *selector, float frame)
{
    unsigned int enc = *h;
    if ((int *)dldObj(h, enc)[2] == &_AnimObjDef) {
        AnimationDefinition *d = (AnimationDefinition *)dldEntry(h, enc);
        char *motion;
        if (d->animation == 0)
            iosJumpRecoverPoint(RO_0013E670, d->name);
        motion = *(char **)(d->animation + 0x20);
        getMotionFloatFrame(output, motion, selector[1], frame);
    } else if ((int *)dldObj(h, *h)[2] == &_BlendMotionDef) {
        func_00039858(output, dldEntry(h, *h), selector, *h, frame);
    }
}
#endif
