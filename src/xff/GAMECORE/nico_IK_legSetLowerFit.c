typedef float Vec4[4] __attribute__((aligned(16)));

typedef struct {
    char pad0[8];
    char *frames;
    char padC[0x24 - 0xC];
    char *table;
} IKAnim;

typedef struct {
    void *obj;
    char *quats;
    char pad8[4];
    char *baseQuats;
    IKAnim *anim;
    int node;
} IKLeg;

extern int B_0018A560;
extern char *GetCharacterClass(void *);
extern void SetQuaternionByAxisRotateVWithNoRegularizeRadian(float *, float *, float);

static inline void quatUpAxis(float *out, float *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vaddy.z vf6, vf0, vf7y\n"
                         "vsubw.z vf6, vf6, vf7w\n"
                         "vsubx.y vf6, vf0, vf5x\n"
                         "vsubz.y vf6, vf6, vf5z\n"
                         "vaddz.x vf6, vf7, vf7z\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.y vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void quatMul(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatConj(float *out, float *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

void nico_IK_legSetLowerFit(IKLeg *leg)
{
    Vec4 q;
    Vec4 rot;
    Vec4 axis;
    Vec4 inv;
    char *e;
    IKAnim *anim;
    int j;

    e = *(char **)(GetCharacterClass(leg->obj) + 0x31C) + B_0018A560 * 0xD0;
    quatUpAxis(axis, (float *)(e + 0xA0));
    SetQuaternionByAxisRotateVWithNoRegularizeRadian(rot, axis, -*(float *)(e + 0xC0));
    quatMul(q, rot, (float *)(e + 0xA0));
    quatMul(q, q, (float *)(e + 0x90));
    anim = leg->anim;
    j = *(int *)(anim->table + B_0018A560 * 0x40 + 0x30);
    quatConj(inv, (float *)(leg->baseQuats + *(int *)(anim->frames + j * 0x40 + 0x38) * 0x10));
    quatMul((float *)(leg->quats + leg->node * 0x10), inv, q);
}
