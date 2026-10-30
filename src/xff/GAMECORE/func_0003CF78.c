typedef struct {
    float f[4];
} __attribute__((aligned(16))) V4;

typedef struct {
    void *id;
    void *ptn;
    void *a;
    int b;
    int c;
    int d;
    void *e;
    void *func;
    int f;
    int g;
    int h;
} LWSSetup;

extern int DldSysUndefSymbol;
extern char rootPtn[];
extern float IdentityQuaternion[];
extern int GetSkeletonFocusNode(void *);
extern void SetGeometryPointerNodePosState(void *, void *, int, float *, V4 *);
extern void *CreateScriptAnimationSequence(LWSSetup *);
extern void _SCRStartLWS(void *, int, int, int);
extern int GetAnimationDefObjLeaveType(int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static void *func_0003CF78(void *obj, char *p)
{
    char work[0x40];
    V4 pos;
    V4 t;
    LWSSetup s;
    char *def = dldResolve((unsigned int *)(p + 0x20));
    void *seq;
    int node;

    if (def != 0) {
        node = GetSkeletonFocusNode(p + 8);
        {
            float z = *(float *)(p + 0x14);
            float y = *(float *)(p + 0x10);
            float x = *(float *)(p + 0xC);
            t.f[0] = x;
            t.f[1] = y;
            t.f[2] = z;
            t.f[3] = 1.0f;
            pos = t;
        }
        SetGeometryPointerNodePosState(work, obj, node, IdentityQuaternion, &pos);
        s.id = def;
        s.ptn = rootPtn;
        s.a = work;
        s.b = 0;
        s.c = 0;
        s.d = 0;
        s.e = obj;
        s.func = 0;
        s.f = 0;
        s.g = 1;
        s.h = -1;
        seq = CreateScriptAnimationSequence(&s);
        _SCRStartLWS(seq, -1, *(int *)(def + 0x1C), 0);
        if (!GetAnimationDefObjLeaveType(*(int *)(def + 0x1C)))
            seq = 0;
        return seq;
    }
    return 0;
}
