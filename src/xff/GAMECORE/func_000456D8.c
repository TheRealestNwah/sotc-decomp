/* Parked: 7 diffs, same length. Builds the rotation turning the direction at 0xC0 toward the target at 0xE0 (seen from 0xB0), writes the scaled, rotated half-arc point to out and the unit target direction to dir. Remaining: the Original loads 32768.0f and the axis argument before the first mul.s of the angle and pi after it; gcc does the mul first. Opaque constants and a separate angle local did not move it. The empty asm on half stops gcc keeping 0.5f in $f20 across the acos call. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char XUnitVector[];
extern char YUnitVector[];
extern char ZUnitVector[];
extern float iosGetACosfExact(float);
extern void GetDifferencialQuaternionWithNoRegularize(void *, void *, void *, void *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, short, void *);

static inline void quatRotA(Vec4 *out0, Vec4 *quat0, Vec4 *vec0)
{
    register Vec4 *out __asm__("$2") = out0;
    Vec4 *vec = vec0;
    register Vec4 *quat __asm__("$3") = quat0;
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%2)\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(vec), "r"(quat) : "memory");
}

static inline void quatRotB(Vec4 *out, Vec4 *quat0, Vec4 *vec)
{
    register Vec4 *quat __asm__("$2") = quat0;
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%2)\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(vec), "r"(quat) : "memory");
}

static inline void vecNormalize(Vec4 *dst, Vec4 *src)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src) : "memory");
}

/* Builds the rotation that turns the direction at 0xC0 toward the target at 0xE0 (seen from 0xB0), and writes
   the halfway point of the rotated arc to out and the unit direction to the target to dir. */
static void func_000456D8(char *o, Vec4 *out0, Vec4 *dir)
{
    register Vec4 *out __asm__("$16") = out0;
    Vec4 q;
    Vec4 d;
    Vec4 axis;
    Vec4 dq;
    Vec4 iq;
    float len;
    float dot;
    float half;
    float acs;
    Vec4 *pos = (Vec4 *)(o + 0xB0);
    register Vec4 *fwd __asm__("$18");
    register Vec4 *ax __asm__("$17");

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(&d), "r"(o + 0xE0), "r"(pos) : "memory");
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(&d) : "$2");
    vecNormalize(&d, &d);
    fwd = (Vec4 *)(o + 0xC0);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(&d), "r"(fwd) : "$2");
    if (dot < 0.0f ? -0.999f < dot : dot < 0.999f) {
        ax = &axis;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                             "lqc2 vf6, 0x0(%2)
"
                             "vopmula.xyz ACC, vf5, vf6
"
                             "vopmsub.xyz vf7, vf6, vf5
"
                             "vsub.w vf7, vf7, vf7
"
                             "sqc2 vf7, 0x0(%0)
"
                             : : "r"(ax), "r"(&d), "r"(fwd) : "memory");
        vecNormalize(ax, ax);
    } else {
        GetDifferencialQuaternionWithNoRegularize(&dq, YUnitVector, &d, XUnitVector);
        __asm__ __volatile__("lqc2 vf11, 0x0(%1)
"
                             "vsubw.x vf5, vf0, vf0w
"
                             "vmulx.xyz vf11, vf11, vf5x
"
                             "sqc2 vf11, 0x0(%0)
"
                             : : "r"(&iq), "r"(&dq) : "memory");
        axis.q = *(s128 *)ZUnitVector;
        ax = &axis;
        quatRotA(ax, &iq, ax);
    }
    acs = iosGetACosfExact(dot);
    half = 0.5f;
    __asm__("" : "+f"(half));
    __asm__("" : "+f"(acs));
    SetQuaternionByAxisRotateVWithNoRegularize(&q, (int)(acs * half * 32768.0f / 3.14159251f), ax);
    quatRotB(out, &q, fwd);
    {
        float h = len * 0.5f;

        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %1, vf6\n"
                             "vmulx.xyzw vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(out), "r"(h) : "memory");
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%0)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(pos) : "memory");
    dir->q = d.q;
}
#endif
