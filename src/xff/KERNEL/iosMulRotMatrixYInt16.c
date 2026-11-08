extern float UnitMatrix[];
extern float iosGetTableSin(short);
extern float iosGetTableCos(short);

void iosMulRotMatrixYInt16(float *out, float *m, short ang)
{
    float rot[16] __attribute__((aligned(16)));
    float c = iosGetTableCos(ang);
    float s = iosGetTableSin(ang);

    __asm__ __volatile__("lq $9, 0x30(%1)
"
                         "sq $9, 0x30(%0)
"
                         "lq $8, 0x20(%1)
"
                         "sq $8, 0x20(%0)
"
                         "lq $7, 0x10(%1)
"
                         "sq $7, 0x10(%0)
"
                         "lq $6, 0x0(%1)
"
                         "sq $6, 0x0(%0)
"
                         : : "r"(rot), "r"(UnitMatrix) : "$6", "$7", "$8", "$9", "memory");
    rot[0] = c;
    rot[2] = -s;
    rot[8] = s;
    rot[10] = c;
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)
"
                         "lqc2 vf15, 0x10(%1)
"
                         "lqc2 vf16, 0x20(%1)
"
                         "lqc2 vf17, 0x30(%1)
"
                         "lqc2 vf24, 0x0(%2)
"
                         "lqc2 vf25, 0x10(%2)
"
                         "lqc2 vf26, 0x20(%2)
"
                         "lqc2 vf27, 0x30(%2)
"
                         "vmulax.xyzw ACC, vf14, vf24x
"
                         "vmadday.xyzw ACC, vf15, vf24y
"
                         "vmaddaz.xyzw ACC, vf16, vf24z
"
                         "vmaddw.xyzw vf24, vf17, vf24w
"
                         "vmulax.xyzw ACC, vf14, vf25x
"
                         "vmadday.xyzw ACC, vf15, vf25y
"
                         "vmaddaz.xyzw ACC, vf16, vf25z
"
                         "vmaddw.xyzw vf25, vf17, vf25w
"
                         "vmulax.xyzw ACC, vf14, vf26x
"
                         "vmadday.xyzw ACC, vf15, vf26y
"
                         "vmaddaz.xyzw ACC, vf16, vf26z
"
                         "vmaddw.xyzw vf26, vf17, vf26w
"
                         "vmulax.xyzw ACC, vf14, vf27x
"
                         "vmadday.xyzw ACC, vf15, vf27y
"
                         "vmaddaz.xyzw ACC, vf16, vf27z
"
                         "vmaddw.xyzw vf27, vf17, vf27w
"
                         "sqc2 vf24, 0x0(%0)
"
                         "sqc2 vf25, 0x10(%0)
"
                         "sqc2 vf26, 0x20(%0)
"
                         "sqc2 vf27, 0x30(%0)
"
                         : : "r"(out), "r"(m), "r"(rot) : "memory");
}
