/* Parked at 24 diffs: the Original keeps &pos in s0 and q in s1 (swapped here), the matrix pointers in v0/v1 are swapped, and the first three zero stores are ordered 0, 0xC, 8. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
#define VU_INVERSE_MATRIX(dst, src) \
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n" \
                         "vsubw.x vf25, vf0, vf0w\n" \
                         "vmulx.xyz vf28, vf24, vf25x\n" \
                         "vsub.w vf28, vf28, vf28\n" \
                         "lq $8, 0x0(%1)\n" \
                         "lq $9, 0x10(%1)\n" \
                         "lq $10, 0x20(%1)\n" \
                         "qmfc2 $11, vf0\n" \
                         "pextlw $12, $9, $8\n" \
                         "pextuw $13, $9, $8\n" \
                         "pextlw $14, $11, $10\n" \
                         "pextuw $15, $11, $10\n" \
                         "pcpyld $8, $14, $12\n" \
                         "pcpyud $9, $12, $14\n" \
                         "pcpyld $10, $15, $13\n" \
                         "pcpyud $11, $13, $15\n" \
                         "qmtc2 $8, vf24\n" \
                         "qmtc2 $9, vf25\n" \
                         "qmtc2 $10, vf26\n" \
                         "vmulax.xyzw ACC, vf24, vf28x\n" \
                         "vmadday.xyzw ACC, vf25, vf28y\n" \
                         "vmaddaz.xyzw ACC, vf26, vf28z\n" \
                         "vmaddw.xyzw vf29, vf0, vf28w\n" \
                         "vsub.w vf29, vf29, vf29\n" \
                         "vadd.w vf29, vf29, vf0\n" \
                         "sqc2 vf24, 0x0(%0)\n" \
                         "sqc2 vf25, 0x10(%0)\n" \
                         "sqc2 vf26, 0x20(%0)\n" \
                         "sqc2 vf29, 0x30(%0)\n" \
                         : : "r"(dst), "r"(src) \
                         : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory")

#define VU_APPLY(out, mtx, v) \
    __asm__ __volatile__("lqc2 vf8, 0(%2)\n" \
                         "lqc2 vf14, 0(%1)\n" \
                         "lqc2 vf15, 16(%1)\n" \
                         "lqc2 vf16, 32(%1)\n" \
                         "lqc2 vf17, 48(%1)\n" \
                         "vmulax.xyzw ACC, vf14, vf8x\n" \
                         "vmadday.xyzw ACC, vf15, vf8y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf8z\n" \
                         "vmaddw.xyzw vf10, vf17, vf8w\n" \
                         "sqc2 vf10, 0(%0)\n" \
                         : : "r"(out), "r"(mtx), "r"(v) : "memory")

extern void GetGeometryPointerPosition(Vec4 *, void *);

void charrootdyn_getLocalYGlobalXZOffsetFromParentGP(Vec4 *local, Vec4 *global, float *q, Vec4 *offset, void *gp)
{
    Vec4 v;
    Vec4 pos;
    Vec4 m[4];
    Vec4 inv[4];
    Vec4 *pp = &pos;

    v.q = offset->q;
    GetGeometryPointerPosition(pp, gp);
    __asm__ __volatile__(".set noreorder\n"
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
        "sqc2 vf14, 0x0(%1)\n"
        "sqc2 vf15, 0x10(%1)\n"
        "sqc2 vf16, 0x20(%1)\n"
        "lqc2 vf4, 0x0(%2)\n"
        "vmove.w vf4, vf0\n"
        "sqc2 vf4, 0x30(%1)\n"
        ".set reorder\n"
        : : "r"(q), "r"(m[0].f), "r"(pp));
    VU_INVERSE_MATRIX(inv, m);
    VU_APPLY(local, inv, &v);
    v.q = local->q;
    {
        float z = 0.0f;
        local->f[3] = z;
        local->f[2] = z;
        local->f[0] = z;
        v.f[3] = z;
        v.f[1] = z;
        VU_APPLY(global, m, &v);
        global->f[1] = z;
    }
}
#endif
