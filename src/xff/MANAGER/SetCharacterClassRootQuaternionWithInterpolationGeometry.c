typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void DivQuaternion(char *, Vec4 *, Vec4 *);
extern void MultiGlobalQuaternionToRootSkeleton(void *, void *, void *);
extern void SetLayoutClassRootQuaternion(char *, Vec4 *);
void SetCharacterClassRootQuaternionWithInterpolationGeometry(char *c, Vec4 *q)
{
    Vec4 delta;
    DivQuaternion((char *)&delta, q, *(Vec4 **)(c + 0x13C));
    MultiGlobalQuaternionToRootSkeleton(*(void **)(c + 0x2DC), &delta, *(void **)(c + 0x358));
    SetLayoutClassRootQuaternion(c, q);
    __asm__ __volatile__("lqc2 vf11, 0(%1)\n"
                         "lqc2 vf12, 0(%2)\n"
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
                         "sqc2 vf13, 0(%0)\n"
                         : : "r"(c + 0x470), "r"(*(void **)(c + 0x13C)), "r"(c + 0x490) : "memory");
}

