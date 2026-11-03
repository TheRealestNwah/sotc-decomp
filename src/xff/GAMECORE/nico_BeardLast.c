typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

typedef struct GlobalVar {
    char pad0[0x194];
    float unk194;
} GlobalVar;

typedef struct BeardWork {
    Vec4 pos;
    Vec4 unk10;
    Vec4 unk20;
    char pad30[0x10];
    float vel[4];
    int initialized;
} BeardWork;

typedef struct CharacterClass {
    char pad0[0x110C];
    BeardWork *beard;
} CharacterClass;

typedef struct BeardArg {
    int chara;
    Vec4 *unk4;
    char *matrices;
    Vec4 *unkC;
    char *unk10;
    int index;
} BeardArg;

extern GlobalVar gcGlobalVar;
extern int D_0017B8BC;
extern int D_0017B8C0;
extern CharacterClass *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern void nico_BeardNext(BeardArg *);
extern void GetMotionNodeQuaternionPos(float *, float *, int, int, int);

static inline void quatAxisZ(float *dst, float *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)
"
                         "vmul.xyzw vf5, vf4, vf4
"
                         "vmr32.xyzw vf6, vf4
"
                         "vmul.xyzw vf7, vf6, vf4
"
                         "vmr32.xyzw vf6, vf6
"
                         "vmul.xyzw vf8, vf6, vf4
"
                         "vsubx.z vf6, vf0, vf5x
"
                         "vsuby.z vf6, vf6, vf5y
"
                         "vaddw.y vf6, vf7, vf7w
"
                         "vsuby.x vf6, vf8, vf8y
"
                         "vsub.w vf6, vf0, vf0
"
                         "vadd.w vf5, vf0, vf0
"
                         "vmulw.xyz vf6, vf6, vf5w
"
                         "vaddw.z vf6, vf6, vf0w
"
                         "sqc2 vf6, 0x0(%0)
"
                         : : "r"(dst), "r"(q) : "memory");
}

static inline float lengthXYZ(float *v)
{
    float d;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)
"
                         "vmul.xyz vf7, vf7, vf7
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vsqrt Q, vf7w
"
                         "vwaitq
"
                         "cfc2 $2, $vi22
"
                         "mtc1 $2, %0
"
                         : "=f"(d) : "r"(v) : "$2");
    return d;
}

static inline void vecMulXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vmul.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecAddXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vadd.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

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

void nico_BeardLast(BeardArg *arg)
{
    int chara = arg->chara;
    BeardWork *beard = GetCharacterClass(chara)->beard;
    Vec4 t;
    Vec4 q;
    Vec4 pos;

    nico_BeardNext(arg);
    beard += D_0017B8BC;
    GetMotionNodeQuaternionPos(q.f, pos.f, chara, arg->index, 1);
    quatAxisZ(t.f, q.f);
    vecScaleXYZ(t.f, t.f, lengthXYZ((float *)(*(char **)(arg->unk10 + 8) + arg->index * 0x40 + 0x10)));
    vecMulXYZ(t.f, t.f, (float *)(GetLayoutClass(chara) + 0x90));
    vecAddXYZ(t.f, t.f, pos.f);
    if (beard->initialized) {
        vecSubXYZ(beard->vel, t.f, beard->pos.f);
        vecScaleXYZ(beard->vel, beard->vel, gcGlobalVar.unk194);
        beard->vel[3] = 1.0f;
    } else {
        vecZero(beard->vel);
        beard->initialized = 1;
    }
    beard->pos.q = t.q;
}
