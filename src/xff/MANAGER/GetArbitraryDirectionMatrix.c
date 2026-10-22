typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern void iosGetArbitraryUpVectorElement(float *, float *);
extern void GetQuaternionByAxisDirZYExact(float *, float *, float *);

int GetArbitraryDirectionMatrix(float *out, float *pos, float *target)
{
    Vec4 dir;
    Vec4 up;
    Vec4 rotation;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dir.f), "r"(target), "r"(pos) : "memory");
    if (dir.f[0] == 0.0f && dir.f[0] == dir.f[1] && dir.f[1] == dir.f[2]) {
        return 0;
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dir.f), "r"(dir.f) : "memory");
    iosGetArbitraryUpVectorElement(up.f, dir.f);
    GetQuaternionByAxisDirZYExact(rotation.f, dir.f, up.f);
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
        : : "r"(rotation.f), "r"(out), "r"(pos) : "memory");
    return 1;
}
