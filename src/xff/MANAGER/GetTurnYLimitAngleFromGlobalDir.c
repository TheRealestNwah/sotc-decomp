#ifdef NONMATCHING /* 139 diffs (146 vs 147 words): early a0/a3 stack-address preloads, m/inv layout order; draft from quat->matInverse->apply->atan2 clamp */
typedef int s128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));

extern char YUnitVector[];
extern unsigned char IdentityQuaternion[];
extern void iosGetStabXZVector(float *, float *);
extern float iosGetATan2fExact(float, float);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);

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


float GetTurnYLimitAngleFromGlobalDir(float *out, float *quat, float *vec, float limit)
{
    Vec4 stab;
    Vec4 dir;
    Vec4 m[4];
    Vec4 inv[4];
    Vec4 rot;
    float ang;
    float t;

    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w
"
                         "lqc2 vf11, 0x0(%0)
"
                         "vmr32.w vf14, vf0
"
                         "vmr32.w vf15, vf0
"
                         "vmr32.w vf16, vf0
"
                         "vopmula.xyz ACC, vf11, vf12
"
                         "vmadd.xyz vf11, vf0, vf0
"
                         "vmadd.xyz vf10, vf11, vf12
"
                         "vmul.xyz vf13, vf11, vf10
"
                         "vopmula.xyz ACC, vf11, vf10
"
                         "vmaddw.xyz vf15, vf10, vf11w
"
                         "vmsubw.xyz vf16, vf10, vf11w
"
                         "vopmula.xyz ACC, vf13, vf12
"
                         "vmadd.xyz vf17, vf13, vf12
"
                         "vopmula.xyz ACC, vf15, vf12
"
                         "vmadd.xyz vf15, vf0, vf0
"
                         "vsub.xyz vf14, vf12, vf17
"
                         "vmove.yz vf17, vf14
"
                         "vmove.y vf14, vf16
"
                         "vmove.y vf16, vf15
"
                         "vmove.y vf15, vf17
"
                         "vmove.z vf14, vf15
"
                         "vmove.z vf15, vf16
"
                         "vmove.z vf16, vf17
"
                         "sqc2 vf14, 0x0(%1)
"
                         "sqc2 vf15, 0x10(%1)
"
                         "sqc2 vf16, 0x20(%1)
"
                         : : "r"(quat), "r"(m) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(&m[3]) : "memory");
    matInverse((float *)inv, (float *)m);
    matApply(dir, (float *)inv, vec);
    iosGetStabXZVector(stab, dir);
    ang = iosGetATan2fExact(stab[0], stab[2]);
    if (ang < 0.0f ? limit < -ang : limit < ang) {
        t = limit;
        if (ang < 0.0f)
            t = -t;
        ang = t;
    }
    SetQuaternionByAxisRotateVWithNoRegularize(rot, -(short)(int)(ang * 32768.0f / 3.14159274f), YUnitVector);
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)
"
                         "lqc2 vf12, 0x0(%1)
"
                         "vmul.xyzw vf13, vf11, vf12
"
                         "vaddy.x vf13, vf13, vf13y
"
                         "vaddz.x vf13, vf13, vf13z
"
                         "vsubx.w vf13, vf13, vf13x
"
                         "vmulw.xyz vf14, vf12, vf11w
"
                         "vmulw.xyz vf15, vf11, vf12w
"
                         "vopmula.xyz ACC, vf12, vf11
"
                         "vopmsub.xyz vf16, vf11, vf12
"
                         "vadd.xyz vf13, vf14, vf15
"
                         "vadd.xyz vf13, vf13, vf16
"
                         "sqc2 vf13, 0x0(%2)
"
                         : : "r"(IdentityQuaternion), "r"(rot), "r"(out) : "memory");
    return ang;
}
#endif
