typedef struct FogColMan {
    char pad0[0x98];
    char free[8];
} FogColMan;
extern FogColMan B_00148A40;
extern unsigned char *_isysCreateObj(void *, int, int, int, int, int);
extern void *memset(void *, int, unsigned int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
typedef union {
    float f;
    int i;
} Word;
typedef struct {
    char pad0[0x4E];
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char pad51[7];
    float near;
    float far;
    float density;
    float min;
    float max;
} FogColClass;
typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float r, g, b;
    float pad0C;
    float near0, far0, max0;
    float pad1C;
    float near1, far1, max1;
} FogParam;
typedef struct {
    char pad00[0x4E];
    unsigned char r, g, b;
    char pad51[0x58 - 0x51];
    float near0, far0, max0;
    float near1, far1, max1;
} FogObj;
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

static void func_00072348(void);

static inline unsigned char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return obj + 0x20;
    }
    return 0;
}

void CreateFogColMan(void *heap)
{
    FogColMan *man = &B_00148A40;
    unsigned char *obj;
    unsigned char *work;
    int i;

    for (i = 0; i < 0x80; i++) {
        obj = _isysCreateObj(heap, 0x18, 0xB0, 0xB0, (int)func_00072348, 0x10);
        if (obj == 0) {
            continue;
        }
        work = GetObjWork(obj, 0x18);
        if (work != 0) {
            memset(work, 0, 0x90);
        }
        *(short *)(work + 0x4C) = i;
        isysAddGroupWithLinkParam(obj, man->free, 0, 0);
    }
}

void SetInitFogColClassFromStageData(Word *data)
{
    FogColClass *fog = (FogColClass *)&B_00148A40;

    fog->near = data[1].f;
    fog->far = data[2].f;
    fog->min = data[3].f;
    fog->max = data[4].f;
    fog->density = data[6].i;
    fog->r = data[7].i;
    fog->g = data[8].i;
    fog->b = data[9].i;
}

void UpdateFogAnim(char *output, char *animation)
{
    Vec4 v;
    float maximum;
    Vec4 *source = (Vec4 *)(animation + 0x10);
    *(s128 *)output = source[0].q;
    *(s128 *)(output + 0x10) = source[1].q;
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(output + 0x20), "r"(source + 2), "r"(0.5f) : "memory");
    maximum = *(float *)(output + 0x30);
    if (maximum < *(float *)(output + 0x34)) maximum = *(float *)(output + 0x34);
    if (maximum < *(float *)(output + 0x38)) maximum = *(float *)(output + 0x38);
    v.f[0] = maximum;
    v.f[1] = maximum;
    v.f[2] = maximum;
    __asm__ __volatile__("lqc2 vf7, 0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(maximum) : "r"(v.f) : "$2");
    *(float *)(output + 0x48) = maximum;
}

void UpdateFogCol(FogObj *o, FogParam *p)
{
    o->r = (unsigned int)p->r;
    o->g = (unsigned int)p->g;
    o->b = (unsigned int)p->b;
    o->near0 = p->near0;
    o->far0 = p->far0;
    o->max0 = p->max0;
    o->near1 = p->near1;
    o->far1 = p->far1;
    o->max1 = p->max1;
}

void SetFogColAvailableFlag(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x80)) = arg1;
}

int IsEnvelopeFogType(char *p)
{
    if (*(int *)(p + 0x40) & 0x800) {
        return 1;
    }
    return 0;
}

void *GetFogColMan(void)
{
    return &B_00148A40;
}

char *GetFogColClass(unsigned char *p)
{
    if (p[0x8] != 0x18) {
        return 0;
    }
    return (char *)p + 0x20;
}

void ForceFogColFlagEnvelope(void *arg0)
{
    (*(int *)((char *)(arg0) + 0x40)) = (int) (((*(int *)((char *)(arg0) + 0x40)) | 0x800) & ~0x400);
}

float getOutSideVectorXYZSquare(char *p)
{
    Vec4 v;
    float m = *(float *)(p + 0x30);
    float r;
    if (m < *(float *)(p + 0x34))
        m = *(float *)(p + 0x34);
    if (m < *(float *)(p + 0x38))
        m = *(float *)(p + 0x38);
    v.f[0] = m;
    v.f[1] = m;
    v.f[2] = m;
    __asm__ __volatile__("lqc2 vf07, 0(%1)\n"
                         "vmul.xyz vf07, vf07, vf07\n"
                         "vaddy.x vf07, vf07, vf07y\n"
                         "vaddz.x vf07, vf07, vf07z\n"
                         "qmfc2 %0, vf07\n"
                         : "=r"(r) : "r"(&v));
    return r;
}

static void func_00072348(void)
{
}
