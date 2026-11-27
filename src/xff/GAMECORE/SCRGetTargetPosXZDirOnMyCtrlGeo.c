/* Target direction on the character's own control geometry: delta of the target from the character position (vsub.xyzw), quaternion at +0x470 converted to a basis (27-instruction VU0 run), transpose via MMI (pextlw/pcpyld) into a world-to-local matrix, apply to the delta, zero y, normalise with vrsqrt (Q read by cfc2.ni) and 1.0f / q, scale. Locals in one struct (quat +0, matrix rows +0x10..0x4F, 0x20 pad). The empty-clobber zero store makes gcc rematerialise &matrix like the Original. */
typedef int s128 __attribute__((mode(TI)));

extern char *GetCharacterClass(int);

void SCRGetTargetPosXZDirOnMyCtrlGeo(float *out, int obj, float *target)
{
    struct {
        s128 quat;
        s128 m[4];
        s128 pad[2];
    } L __attribute__((aligned(16)));
    char *c;
    register float q __asm__("$f0");
    float inv;

    c = GetCharacterClass(obj);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%2)\n"
                         :
                         : "r"(target), "r"(*(float **)(c + 0x134)), "r"(out)
                         : "memory");
    L.quat = *(s128 *)(c + 0x470);
    {
        register s128 *m0 __asm__("$2") = &L.m[0];
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
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
                         :
                         : "r"(&L.quat), "r"(m0)
                         : "memory");
    }
    {
        register s128 *m3 __asm__("$3") = &L.m[3];
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(m3));
    }
    {
        register s128 *m0 __asm__("$2") = &L.m[0];
    __asm__ __volatile__("lqc2 vf24, 0x30(%0)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%0)\n"
                         "lq $9, 0x10(%0)\n"
                         "lq $10, 0x20(%0)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         "lqc2 vf8, 0x0(%1)\n"
                         "lqc2 vf14, 0x0(%0)\n"
                         "lqc2 vf15, 0x10(%0)\n"
                         "lqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf17, 0x30(%0)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%1)\n"
                         :
                         : "r"(m0), "r"(out)
                         : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
    }
    *(int *)(out + 1) = 0;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(q)
                         : "r"(out)
                         : "$2", "memory");
    inv = 1.0f / q;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         :
                         : "r"(out), "r"(inv)
                         : "memory");
}
