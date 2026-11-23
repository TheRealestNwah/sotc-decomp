/* Classifies pos against the attain range at w+0x3E0, seen from the camera:
 * 1 in range, 5 in range but outside the angle, otherwise 0 outside the
 * angle, 3 too near, 2 too far, 4 above or below. */

typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    s128 pos;
    float lo;
    float hi;
    float ang;
    float h;
} Range;

extern void iosUnitMatrix(Vec4 *);
extern void StabilizeToYRotQuaternion(void *);
extern float iosGetATan2fExact(float, float);

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void matMul(Vec4 *dst, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "lqc2 vf24, 0x0(%2)\n"
                         "lqc2 vf25, 0x10(%2)\n"
                         "lqc2 vf26, 0x20(%2)\n"
                         "lqc2 vf27, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf24x\n"
                         "vmadday.xyzw ACC, vf15, vf24y\n"
                         "vmaddaz.xyzw ACC, vf16, vf24z\n"
                         "vmaddw.xyzw vf24, vf17, vf24w\n"
                         "vmulax.xyzw ACC, vf14, vf25x\n"
                         "vmadday.xyzw ACC, vf15, vf25y\n"
                         "vmaddaz.xyzw ACC, vf16, vf25z\n"
                         "vmaddw.xyzw vf25, vf17, vf25w\n"
                         "vmulax.xyzw ACC, vf14, vf26x\n"
                         "vmadday.xyzw ACC, vf15, vf26y\n"
                         "vmaddaz.xyzw ACC, vf16, vf26z\n"
                         "vmaddw.xyzw vf26, vf17, vf26w\n"
                         "vmulax.xyzw ACC, vf14, vf27x\n"
                         "vmadday.xyzw ACC, vf15, vf27y\n"
                         "vmaddaz.xyzw ACC, vf16, vf27z\n"
                         "vmaddw.xyzw vf27, vf17, vf27w\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf27, 0x30(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void matApply(float *out, Vec4 *m, float *v)
{
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
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline float vecLength(float *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

int chkAttainExecOffsetData(char *w0, float *pos0, char *cam0, float *off0, char *src0, float ext)
{
    register char *w __asm__("$19") = w0;
    register float *pos __asm__("$21") = pos0;
    register char *cam __asm__("$18") = cam0;
    register float *off __asm__("$16") = off0;
    register char *src __asm__("$17") = src0;
    Vec4 m[4];
    Vec4 unit[4];
    Vec4 d;
    Vec4 c;
    Vec4 q;
    register Range *r __asm__("$20");
    Vec4 *qp;
    register float *cp __asm__("$2");
    register int flag __asm__("$2");
    register s128 tq __asm__("$3");
    register float lo __asm__("$f1");
    float far, len, y, ang;
    register Vec4 *mA __asm__("$2");
    register float *pp __asm__("$3");
    register int t0 __asm__("$8"), t1 __asm__("$9"), t2 __asm__("$10"), t3 __asm__("$11"), t4 __asm__("$12"), t5 __asm__("$13"), t6 __asm__("$14"), t7 __asm__("$15");

    r = (Range *)(w + 0x3E0);
    __asm__("" : "+r"(w), "+r"(pos), "+r"(cam), "+r"(off), "+r"(src));
    __asm__("" : "+r"(r));
    lo = r->lo;
    far = lo + (r->hi - lo);
    iosUnitMatrix(unit);
    tq = r->pos;
    unit[3].q = tq;
    cp = *(float **)(cam + 0x134);
    unit[3].f[3] = 1.0f;
    vecAdd(c.f, cp, off);
    tq = *(s128 *)(src + 0x470);
    flag = *(int *)(w + 0xE8);
    c.f[3] = 1.0f;
    q.q = tq;
    if (flag != 0) {
        qp = &q;
        StabilizeToYRotQuaternion(qp);
    } else
        qp = &q;
    pp = c.f;
    mA = m;
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
                         "lqc2 vf4, 0x0(%2)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(mA), "r"(qp), "r"(pp));
    matMul(m, m, unit);
    __asm__ __volatile__("lqc2 vf24, 0x30(%8)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq %0, 0x0(%8)\n"
                         "lq %1, 0x10(%8)\n"
                         "lq %2, 0x20(%8)\n"
                         "qmfc2.ni %3, vf0\n"
                         "pextlw %4, %1, %0\n"
                         "pextuw %5, %1, %0\n"
                         "pextlw %6, %3, %2\n"
                         "pextuw %7, %3, %2\n"
                         "pcpyld %0, %6, %4\n"
                         "pcpyud %1, %4, %6\n"
                         "pcpyld %2, %7, %5\n"
                         "pcpyud %3, %5, %7\n"
                         "qmtc2.ni %0, vf24\n"
                         "qmtc2.ni %1, vf25\n"
                         "qmtc2.ni %2, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%8)\n"
                         "sqc2 vf25, 0x10(%8)\n"
                         "sqc2 vf26, 0x20(%8)\n"
                         "sqc2 vf29, 0x30(%8)\n"
                         : "=&r"(t0), "=&r"(t1), "=&r"(t2), "=&r"(t3), "=&r"(t4), "=&r"(t5), "=&r"(t6), "=&r"(t7)
                         : "r"(m) : "memory");
    pos[3] = 1.0f;
    matApply(d.f, m, pos);
    y = d.f[1];
    d.f[1] = 0.0f;
    len = vecLength(d.f);
    vecScale(d.f, d.f, 1.0f / len);
    ang = iosGetATan2fExact(d.f[0], d.f[2]);
    if (r->lo <= len && len <= far + ext && __builtin_fabsf(y) <= r->h) {
        if (__builtin_fabsf(ang) <= r->ang)
            return 1;
        return 5;
    }
    if (!(__builtin_fabsf(ang) <= r->ang))
        return 0;
    if (len < r->lo)
        return 3;
    if (far + ext < len)
        return 2;
    if (__builtin_fabsf(y) < r->h)
        return 4;
    return 0;
}
