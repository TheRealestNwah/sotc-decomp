#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
    int i[4];
} Vec4;

typedef struct {
    Vec4 vectors[5];
    int type;
    float values[3];
} JudgeVolume;

void GetCenterPositionOfJudgeVolumeInfo(Vec4 *out, JudgeVolume *volume)
{
    Vec4 m[4];
    Vec4 *mp;
    float h;

    switch (volume->type) {
    case 0:
        mp = m;
        if (volume->values[0] > 5.9690260f && volume->values[1] == 0.0f)
            break;
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
            : : "r"(volume->vectors[1].f), "r"(mp), "r"(volume->vectors[0].f) : "memory");
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(out) : "memory");
        h = volume->vectors[4].f[2] * 0.5f;
        out->f[2] = volume->values[1] * h + h;
        __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                             "lqc2 vf14, 0x0(%2)\n"
                             "lqc2 vf15, 0x10(%2)\n"
                             "lqc2 vf16, 0x20(%2)\n"
                             "lqc2 vf17, 0x30(%2)\n"
                             "vmulax.xyzw ACC, vf14, vf8x\n"
                             "vmadday.xyzw ACC, vf15, vf8y\n"
                             "vmaddaz.xyzw ACC, vf16, vf8z\n"
                             "vmaddw.xyzw vf10, vf17, vf8w\n"
                             "sqc2 vf10, 0x0(%0)\n"
                             : : "r"(out), "r"(out), "r"(m) : "memory");
        return;
    case 1:
        break;
    default:
        return;
    }
    out->q = volume->vectors[0].q;
}
#endif
