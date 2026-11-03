extern int DldSysUndefSymbol;
extern int _AnimObjDef;
extern int _BlendMotionDef;
typedef struct { unsigned char fields[16]; } MotionOption;
typedef struct {
    unsigned char pad0[4];
    short frames;
    unsigned char pad6[0x16];
    MotionOption *options;
} Motion;
extern Motion *getAnimObjResource(unsigned int *);
extern unsigned int *getBlendLastMotion(unsigned int *);
extern void func_00032E98(void *, void *, void *, MotionOption *, int, float);

static inline int *dldObj(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t : 0;
}

int GetMotionOptionNodeFloatFrame(void *a, void *b, void *c, unsigned int *h, int node, float frame)
{
    if ((int *)dldObj(h)[2] == &_AnimObjDef) {
        Motion *m = getAnimObjResource(h);
        func_00032E98(a, b, c, &m->options[node], m->frames, frame);
    } else if ((int *)dldObj(h)[2] == &_BlendMotionDef) {
        return GetMotionOptionNodeFloatFrame(a, b, c, getBlendLastMotion(h), node, frame);
    }
}
