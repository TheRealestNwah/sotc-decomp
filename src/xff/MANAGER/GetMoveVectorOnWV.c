#ifdef NONMATCHING /* 2 diffs: neg.s scheduled before the lwc1 of v[2]; explicit asm addiu for the matrix pointer after iosCopyMatrix keeps it out of a saved reg */
typedef float Vec4[4] __attribute__((aligned(16)));

extern float ZUnitVector[4];
extern float YUnitVectorInv[4];
extern float UnitMatrix[4][4];
extern void iosCopyMatrix(void *, void *);

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


static inline void scaleXYZ(float *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "qmtc2.ni %1, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(v), "r"(s) : "memory");
}

void GetMoveVectorOnWV(float *out, float *vec, float *v2, float *matrix, float speed)
{
    Vec4 tmp;
    Vec4 m[4];
    Vec4 inv[4];
    Vec4 v;
    float y;
    float sign;
    float vx;
    float vz;
    float *mp;

    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "qmtc2.ni %1, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%2)
"
                         : : "r"(v2), "r"(-speed), "r"(tmp) : "memory");
    matInverse((float *)inv, matrix);
    matApply(v, (float *)inv, ZUnitVector);
    y = v[1];
    if (y < 0.0f ? y < -0.707f : 0.707f < y) {
        matApply(v, (float *)inv, YUnitVectorInv);
        sign = y < 0.0f ? -1.0f : 1.0f;
        scaleXYZ(v, sign);
    }
    v[1] = 0.0f;
    scaleXYZ(v, -1.0f);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(v) : "memory");
    iosCopyMatrix(m, UnitMatrix);
    vx = v[0];
    __asm__ __volatile__("addiu %0, $29, 0x10" : "=r"(mp) : "f"(vx));
    vz = v[2];
    m[2][0] = vx;
    m[2][2] = vz;
    m[0][0] = vz;
    m[0][2] = -vx;
    matApply(out, mp, vec);
    scaleXYZ(out, speed);
    out[1] = tmp[1];
}
#endif
