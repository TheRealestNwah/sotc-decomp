typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
    int i[4];
} Vec4;

typedef struct {
    char pad0[0x194];
    float unk194;
} GlobalVar;

typedef struct {
    Vec4 pos;
    Vec4 unk10;
    Vec4 unk20;
    char pad30[0x10];
    float vel[4];
    int initialized;
} BeardWork;

typedef struct {
    char pad0[0x110C];
    BeardWork *beard;
} CharacterClass;

typedef struct {
    int chara;
    Vec4 *unk4;
    char *matrices;
    Vec4 *unkC;
    int unk10;
    int index;
} BeardArg;

extern GlobalVar gcGlobalVar;
extern int D_0017B8BC;
extern int D_0017B8C0;
extern CharacterClass *GetCharacterClass(int);

static inline void vecSubXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecScaleXYZ(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecZero(float *dst)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(dst) : "memory");
}

void nico_BeardTop(BeardArg *arg)
{
    BeardWork *beard = GetCharacterClass(arg->chara)->beard;
    float *pos = (float *)&beard->pos;

    D_0017B8BC = 0;
    if (beard->initialized) {
        vecSubXYZ(beard->vel, (float *)(arg->matrices + arg->index * 0x40 + 0x30), pos);
        vecScaleXYZ(beard->vel, beard->vel, gcGlobalVar.unk194);
    } else {
        vecZero(beard->vel);
        beard->initialized = 1;
    }
    beard->pos.q = ((Vec4 *)(arg->matrices + arg->index * 0x40 + 0x30))->q;
    beard->unk10.q = arg->unkC[arg->index].q;
    beard->unk20.q = arg->unk4[arg->index].q;
    {
        int *p = &D_0017B8BC;
        D_0017B8C0 = 0;
        (*p)++;
    }
}
