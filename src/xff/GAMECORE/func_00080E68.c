/* Parked at 2 diffs: the original sets $a2 = 0x238E before zeroing $f20 for the second matrix. */
#ifdef NONMATCHING
typedef float Vec4[4] __attribute__((aligned(16)));

extern char *GetLayoutClass(void *);
extern void iosMulRotMatrixZInt16(Vec4 *, void *, int);
extern void iosMulRotMatrixXInt16(Vec4 *, Vec4 *, int);
extern void GetMotionNodeQuaternionPos(float *, float *, void *, int, int);
extern void iosTransMatrixF(Vec4 *, Vec4 *, float, float, float);

static inline void quatPosToMatrix(float *out, float *quat, float *pos)
{
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
                         : : "r"(out), "r"(quat) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(pos) : "memory");
}

static inline void matInverse(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2 $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2 $8, vf24\n"
                         "qmtc2 $9, vf25\n"
                         "qmtc2 $10, vf26\n"
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
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}
static inline void matApply(float *out, float *m, float *v)
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

static inline float fsqrtc(float x)
{
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x) : "$f12");
    return r;
}

static inline float fsqrt(float x)
{
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline float lenSqXY(float *v)
{
    float r;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xy vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "qmfc2 $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

static inline void scaleXY(float *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "mfc1 $8, %1\n"
                         "qmtc2 $8, vf6\n"
                         "vmulx.xy vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "f"(s) : "$8", "memory");
}

typedef struct {
    void *obj;
    float radius;
} Collider;

int func_00080E68(float *pos, Collider *c)
{
    Vec4 inv[4];
    Vec4 m[4];
    Vec4 local;
    Vec4 inv2[4];
    Vec4 m2[4];
    Vec4 npos;
    Vec4 local2;
    float d, r, top;
    char *lay;
    int ret;

    ret = 0;
    top = 0.3f;
    lay = GetLayoutClass(c->obj);
    iosMulRotMatrixZInt16(m, *(char **)(lay + 0x158) + 0x5C0, -0x2000);
    iosMulRotMatrixXInt16(m, m, 0xE38);
    iosTransMatrixF(m, m, 0.0f, top, 0.0f);
    matInverse(inv[0], m[0]);
    matApply(local, inv[0], pos);
    if (local[2] < top) {
        d = lenSqXY(local);
        r = c->radius + top;
        if (d < r * r) {
            scaleXY(local, r / fsqrtc(d));
            matApply(pos, m[0], local);
            ret = 1;
        }
    }
    GetMotionNodeQuaternionPos(local, npos, c->obj, 0x10000, 1);
    { float *mp = m2[0]; __asm__("" : "=r"(mp) : "0"(mp)); quatPosToMatrix(mp, local, npos); }
    top = 0.0f;
    iosMulRotMatrixZInt16(m2, m2, 0x238E);
    r = 0.3f;
    iosTransMatrixF(m2, m2, top, r, top);
    matInverse(inv2[0], m2[0]);
    matApply(local2, inv2[0], pos);
    if (top < local2[2]) {
        d = lenSqXY(local2);
        if (d < 0.31f * 0.31f) {
            scaleXY(local2, 0.31f / fsqrt(d));
            matApply(pos, m2[0], local2);
            ret |= 1;
        }
    }
    return ret;
}
#else
extern int func_00080E68(float *pos, int param, float *prev);
#endif
