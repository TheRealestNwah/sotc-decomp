typedef float Vec4[4] __attribute__((aligned(16)));

extern Vec4 YUnitVector;
extern Vec4 ZUnitVector;
extern Vec4 ZUnitVector2 __asm__("ZUnitVector");
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, float *, float *);
extern float iosGetATan2fExact(float, float);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);

/* Parked: 2 words off, only the order of the final `addiu $a2` and `addiu $a0` before the SetQuaternion call. The launder recipe (see asm("" : "+r"(p)) on each stack pointer) fixed everything else. */
#ifdef NONMATCHING
void GetQuaternionByAxisDirZY(float *out, float *dir, float *v)
{
    struct { Vec4 mat[4]; Vec4 t; Vec4 neg; Vec4 rot; } L;
    short ang;
    float *m, *n, *r1, *r2;

    GetDifferencialQuaternionWithNoRegularize(out, dir, ZUnitVector, YUnitVector);
    n = L.neg;
    __asm__("" : "+r"(n));
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(n), "r"(out) : "memory");
    m = L.mat[0];
    __asm__("" : "+r"(m));
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
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
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(m), "r"(n) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"((char *)m + 0x30) : "memory");
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(L.t), "r"(L.mat), "r"(v) : "memory");
    L.t[2] = 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(L.t) : "memory");
    ang = (short)(iosGetATan2fExact(L.t[0], L.t[1]) * 32768.0f / 3.14159274f);
    r1 = L.rot;
    __asm__("" : "+r"(r1));
    SetQuaternionByAxisRotateVWithNoRegularize(r1, ang, ZUnitVector2);
    r2 = L.rot;
    __asm__("" : "+r"(r2));
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
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(r2) : "memory");
}
#else
extern void GetQuaternionByAxisDirZY(float *out, float *dir, float *v);
#endif
