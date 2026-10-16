typedef int s128 __attribute__((mode(TI)));

extern float ZUnitVector[];
extern void nico_neckFitToParentInvDirIK(void *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);

typedef struct {
    int pad0;
    s128 *quats;
    char pad8[0xC];
    int index;
} NeckWork;

void nico_neckFitToParentInvDirIKBankReverse(NeckWork *w)
{
    float r[4] __attribute__((aligned(16)));
    s128 *q;

    nico_neckFitToParentInvDirIK(w);
    q = (s128 *)((w->index << 4) + (int)w->quats);
    SetQuaternionByAxisRotateVWithNoRegularize(r, -0x8000, ZUnitVector);
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
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
                         "sqc2 vf13, 0x0(%2)\n"
                         : : "r"(q), "r"(r), "r"(q) : "memory");
}
