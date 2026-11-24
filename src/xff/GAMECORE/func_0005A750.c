typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
/* Stores through this union may alias other types, keeping the Original store order. */
typedef union { float f; int i; u_long128 q; } FU;
typedef struct ScriptCtrlDef {
    int pad0;
    int status;
} ScriptCtrlDef;

extern ScriptCtrlDef *ScriptCtrlDef_SCRStopL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRStopR;
extern ScriptCtrlDef *ScriptCtrlDef_SCRHorseDash;
extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(int);
extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern float *GetGeometryPointerSurfacePlane(void *);
extern float GetPlaneSlopeDegree(float *);
extern float iosGetATan2fExact(float, float);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline float vdist(float *a, float *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "vmul.xyz vf7, vf7, vf7
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         ".word 0x4BA703BD
"
                         "vwaitq
"
                         "cfc2.ni $2, $vi22
"
                         "mtc1 $2, %0
"
                         : "=f"(r) : "r"(a), "r"(b) : "$2", "memory");
    return r;
}

static inline void vecNormalize(float *dst_, float *src_)
{
    register float *dst __asm__("$2") = dst_;
    register float *src __asm__("$2") = src_;
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

static inline void quatPosToMatrix(float *out_, float *quat_)
{
    register float *out __asm__("$4") = out_;
    register float *quat __asm__("$3") = quat_;
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
}

static inline void matInverse(float *dst_, float *src_)
{
    register float *dst __asm__("$3") = dst_;
    register float *src __asm__("$3") = src_;
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
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

static inline void matApply(float *out_, float *m_, float *v_)
{
    register float *out __asm__("$2") = out_;
    register float *m __asm__("$3") = m_;
    register float *v __asm__("$2") = v_;
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%2)\n"
                         : : "r"(v), "r"(m), "r"(out) : "memory");
}

static int func_0005A750(int obj, char *geom, u_long128 *pos, int useGeom, int flag, float *p60, char *ctrl, unsigned int *scr,
                  float thr, float *outDist, float *outAng)
{
    char *ai = GetSCRCharaAIWorkPtr(obj);
    char *cc = GetCharacterClass(obj);
    char *lc = GetLayoutClass(obj);
    struct {
        Vec4 p, v, m[4];
    } L;
    float *plane;
    float dist, ang, r;
    int st;

    if (flag != 0) {
        *(u_long128 *)L.p = *pos;
        plane = (float *)(pos + 1);
    } else if (useGeom != 0) {
        *(u_long128 *)L.p = *(u_long128 *)(geom + 0x40);
        plane = GetGeometryPointerSurfacePlane(geom);
    } else {
        goto ret0;
    }
    if (!(*(float *)(cc + 0x400) * 57.29578f <= __builtin_fabsf(GetPlaneSlopeDegree(plane))))
        return 0;
    dist = vdist(*(float **)(lc + 0x134), L.p);
    *(u_long128 *)L.v = *(u_long128 *)plane;
    ((FU *)&L.v[1])->f = 0;
    vecNormalize(L.v, L.v);
    quatPosToMatrix(L.m[0], (float *)(cc + 0x470));
    {
        register float *z __asm__("$2") = L.m[3];
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(z));
    }
    matInverse(L.m[0], L.m[0]);
    matApply(L.v, L.m[0], L.v);
    ang = iosGetATan2fExact(L.v[0], L.v[2]);
    ((FU *)outDist)->f = dist;
    *outAng = ang;
    if (!(dist < thr))
        goto ret0;
    *(int *)(ai + 0x41E4) = 0;
    if (scr != 0 && dldResolve(scr + 1) == (char *)ScriptCtrlDef_SCRHorseDash)
        goto stm;
    r = p60[2];
    if (__builtin_fabsf(r) <= **(float **)(ai + 0x41C4)) {
    stm:
        st = *(int *)(ai + 0x41E0);
        if (0 <= ang) {
            if (st == 2 && *(float *)(ai + 0x41E8) < 2.0f) {
                *(int *)(ai + 0x41E4) = 2;
                goto add;
            } else {
                *(float *)(ai + 0x41E8) = 0;
                *(int *)(ai + 0x41E4) = 1;
            }
        } else {
            if (st == 1 && *(float *)(ai + 0x41E8) < 2.0f) {
                *(int *)(ai + 0x41E4) = 1;
            add:
                *(float *)(ai + 0x41E8) += *(float *)(gcGlobalVar + 0x180);
            } else {
                *(float *)(ai + 0x41E8) = 0;
                *(int *)(ai + 0x41E4) = 2;
            }
        }
        p60[2] = 0;
    } else {
        if (0 < r) {
            *(float *)(ai + 0x41E8) = 0;
            *(int *)(ai + 0x41E4) = 1;
        } else {
            *(float *)(ai + 0x41E8) = 0;
            *(int *)(ai + 0x41E4) = 2;
        }
    }
    if (*(int *)(ai + 0x41E4) == 1) {
        *(unsigned long *)(ctrl + 0x1C0) |= 1L << ScriptCtrlDef_SCRStopR->status;
        *(unsigned long *)(ctrl + 0x1C0) &= ~(1L << ScriptCtrlDef_SCRStopL->status);
    } else {
        *(unsigned long *)(ctrl + 0x1C0) |= 1L << ScriptCtrlDef_SCRStopL->status;
        *(unsigned long *)(ctrl + 0x1C0) &= ~(1L << ScriptCtrlDef_SCRStopR->status);
    }
    return 1;
ret0:
    return 0;
}
