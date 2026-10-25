typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
/* Inverse of a rigid transform: transposed rotation, rotated negated translation. */
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


static inline void transformPoint(void *out, void *quaternion, void *position, void *point)
{
    __asm__ __volatile__("lqc2 vf08, 0x0(%0)\n"
                         "lqc2 vf18, 0x0(%1)\n"
                         "vmove.w vf18, vf00\n"
                         : : "r"(point), "r"(position));
    __asm__ __volatile__("vaddw.xyz vf12, vf00, vf00w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf00\n"
                         "vmr32.w vf15, vf00\n"
                         "vmr32.w vf16, vf00\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf00, vf00\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf00, vf00\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf08x\n"
                         "vmadday.xyzw ACC, vf15, vf08y\n"
                         "vmaddaz.xyzw ACC, vf16, vf08z\n"
                         "vmaddw.xyzw vf10, vf18, vf08w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(quaternion) : "memory");
}

extern int GetMotionOptionNodeParentId(void *, int);

int GetCharacterClassMotionInterpNodePosition(Vec4 *out, char *character, int node)
{
    if (node > 0 && (node & 0x10000)) {
        int option = node & ~0x10000;
        if (GetMotionOptionNodeParentId(*(void **)(character + 0x358), option) < 0) {
            transformPoint(out, character + 0x80, character + 0x40,
                (void *)(option * 16 + *(int *)(character + 0x34C)));
        } else {
            out->q = *(s128 *)(option * 16 + *(int *)(character + 0x34C));
        }
        return *(signed char *)(option * 3 + *(int *)(character + 0x2FC) + 1);
    }
    switch (node) {
    case -2: out->q = **(s128 **)(character + 0x134); break;
    case -1: out->q = *(s128 *)(character + 0x460); break;
    default: out->q = *(s128 *)(node * 64 + *(int *)(character + 0x158) + 0x30); break;
    }
    return 1;
}

void GetCharacterClassMotionInterpNodeLastPosition(Vec4 *out, char *character, int node)
{
    Vec4 inverse[4];
    if (node > 0 && (node & 0x10000)) {
        int option = node & ~0x10000;
        if (GetMotionOptionNodeParentId(*(void **)(character + 0x358), option) < 0) {
            void *position = *(void **)(character + 0x138);
            void *offset = (void *)(option * 16 + *(int *)(character + 0x350));
            __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                                 "lqc2 vf6, 0(%2)\n"
                                 "vadd.xyz vf5, vf5, vf6\n"
                                 "sqc2 vf5, 0(%0)\n"
                                 : : "r"(out), "r"(position), "r"(offset) : "memory");
        } else {
            out->q = *(s128 *)(option * 16 + *(int *)(character + 0x350));
        }
    } else {
        switch (node) {
        case -2: out->q = **(s128 **)(character + 0x138); break;
        case -1: out->q = *(s128 *)(character + 0x460); break;
        default:
            VU_INVERSE_MATRIX(inverse, (void *)(node * 64 + *(int *)(character + 0x168)));
            out->q = inverse[3].q;
            break;
        }
    }
}
