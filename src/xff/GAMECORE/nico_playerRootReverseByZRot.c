typedef float Vec4[4] __attribute__((aligned(16)));

extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern Vec4 IdentityQuaternion;
extern Vec4 ZUnitVector;
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);
extern void SetCharacterClassRootQuaternion(char *, float *);

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

static inline void quatRotate(float *out, float *q, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%0)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(q), "r"(v));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}

static inline void rotByAxis(float *out, float *base, short ang, float *axis)
{
    Vec4 rot;

    SetQuaternionByAxisRotateVWithNoRegularize(rot, ang, axis);
    quatMul(out, base, rot);
}

void nico_playerRootReverseByZRot(void *obj)
{
    char *c = GetCharacterClass(obj);
    Vec4 q;
    float *pos;

    rotByAxis(q, IdentityQuaternion, -0x8000, ZUnitVector);
    {
        Vec4 inv;

        quatConj(inv, q);
        pos = (float *)(c + 0x6D0);
        quatRotate(pos, inv, pos);
    }
    quatMul(q, *(float **)(GetLayoutClass(obj) + 0x13C), q);
    SetCharacterClassRootQuaternion(c, q);
}
