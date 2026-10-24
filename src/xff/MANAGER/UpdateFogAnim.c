typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
void UpdateFogAnim(char *output, char *animation)
{
    Vec4 v;
    float maximum;
    Vec4 *source = (Vec4 *)(animation + 0x10);
    *(s128 *)output = source[0].q;
    *(s128 *)(output + 0x10) = source[1].q;
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(output + 0x20), "r"(source + 2), "r"(0.5f) : "memory");
    maximum = *(float *)(output + 0x30);
    if (maximum < *(float *)(output + 0x34)) maximum = *(float *)(output + 0x34);
    if (maximum < *(float *)(output + 0x38)) maximum = *(float *)(output + 0x38);
    v.f[0] = maximum;
    v.f[1] = maximum;
    v.f[2] = maximum;
    __asm__ __volatile__("lqc2 vf7, 0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(maximum) : "r"(v.f) : "$2");
    *(float *)(output + 0x48) = maximum;
}
