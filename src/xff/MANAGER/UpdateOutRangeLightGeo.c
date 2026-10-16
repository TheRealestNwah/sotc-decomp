#define VU_APPLY_MATRIX(dst, m, v) \
    __asm__ __volatile__("lqc2 vf08, 0x0(%2)\n" \
                         "lqc2 vf14, 0x0(%1)\n" \
                         "lqc2 vf15, 0x10(%1)\n" \
                         "lqc2 vf16, 0x20(%1)\n" \
                         "lqc2 vf17, 0x30(%1)\n" \
                         "vmulax.xyzw ACC, vf14, vf08x\n" \
                         "vmadday.xyzw ACC, vf15, vf08y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf08z\n" \
                         "vmaddw.xyzw vf10, vf17, vf08w\n" \
                         "sqc2 vf10, 0x0(%0)\n" \
                         : : "r"(dst), "r"(m), "r"(v) : "memory")
#define VU_QUAT_MUL(dst, a, b) \
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n" \
                         "lqc2 vf12, 0x0(%2)\n" \
                         "vmul.xyzw vf13, vf11, vf12\n" \
                         "vaddy.x vf13, vf13, vf13y\n" \
                         "vaddz.x vf13, vf13, vf13z\n" \
                         "vsubx.w vf13, vf13, vf13x\n" \
                         "vmulw.xyz vf14, vf12, vf11w\n" \
                         "vmulw.xyz vf15, vf11, vf12w\n" \
                         "vopmula.xyz ACC, vf12, vf11\n" \
                         "vopmsub.xyz vf16, vf11, vf12\n" \
                         "vadd.xyz vf13, vf14, vf15\n" \
                         "vadd.xyz vf13, vf13, vf16\n" \
                         "sqc2 vf13, 0x0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")
extern void UpdateGlobalLightOutRange(void *, void *);

void UpdateOutRangeLightGeo(char *c, char *light, void *l2)
{
    if (l2 != 0) {
        VU_QUAT_MUL(light + 0x20, *(void **)(c + 0x13C), light + 0x20);
        VU_APPLY_MATRIX(light + 0x10, *(void **)(c + 0x158), light + 0x10);
        UpdateGlobalLightOutRange(l2, light);
    }
}
