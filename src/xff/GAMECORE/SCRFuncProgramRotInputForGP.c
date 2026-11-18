typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern char *GetAnimationClass(void *);
extern char *GetCharacterClass(void *);
extern float *getGoalPointDataByAreaIdx(char *, int, int);
extern float iosGetATan2fExact(float, float);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void SCRCharaTurnDirectInput(void *, float);
extern void analyzeMotionProperty(void *, char *, float *, float *, int, float, float);
extern void setAttainMotScaleSlowLegCtrlWork(char *, float);
extern int *ScriptCtrlDef_SCRGoR;
extern int *ScriptCtrlDef_SCRGoL;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline float distanceXZ(void *a, void *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         ".word 0x4A2703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void vecNormalize(float *dst, float *src)
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

static inline void matApply(float *out, float *m, float *v)
{
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

static inline float fabsf(float x) { return __builtin_fabsf(x); }
void SCRFuncProgramRotInputForGP(void *obj, int b, int c, int d, int e, int f, unsigned int *mot1, unsigned int *mot2, float deg, float margin)
{
    Vec4 m[4];
    VecQ dir;
    float len1;
    float spd;
    float len2;
    float len3;
    register char *w asm("s3");
    float *goal;
    char *anim;
    char *lay;
    char *chr;
    float dist;
    float a;
    float lim;
    char *m2;

    w = getSCRDataCtrlWork(obj);
    goal = getGoalPointDataByAreaIdx(w, *(int *)(w + 0x3C90), *(int *)(w + 0x3C8C));
    if (goal == 0)
        return;
    anim = GetAnimationClass(obj);
    lay = GetLayoutClass(obj);
    chr = GetCharacterClass(obj);
    dist = distanceXZ(goal, *(void **)(lay + 0x134));
    dist -= margin;
    if (dist < 0.0f)
        dist = 0.0f;
    if (dldResolve(mot1) == *(char **)anim) {
        analyzeMotionProperty(obj, *(char **)anim, &len1, &spd, 0, 1.0f, *(float *)(anim + 0xC));
        m2 = dldResolve(mot2);
        analyzeMotionProperty(obj, m2, &len2, 0, 0, 1.0f, 0.0f);
        setAttainMotScaleSlowLegCtrlWork(w + 0x3D10, dist / (len1 + len2));
        quatPosToMatrix(m[0], *(float **)(lay + 0x13C), *(float **)(lay + 0x134));
        matInverse(m[0], m[0]);
        matApply(dir.f, m[0], goal);
        ((int *)dir.f)[1] = 0;
        vecNormalize(dir.f, dir.f);
        a = iosGetATan2fExact(dir.f[0], dir.f[2]);
        spd = spd / (*(float *)(chr + 0x374) * *(float *)(anim + 0x1C) * *(float *)(chr + 0x524));
        lim = deg * 0.017453293f;
        dist = fabsf(a) / (spd * ((float)*(int *)(*(char **)anim + 0x74) * 0.017453293f));
        dist *= 1.05f;
        if (lim < a) {
            CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRGoR[1]);
            SCRCharaTurnDirectInput(obj, dist);
        } else if (a < -lim) {
            CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRGoL[1]);
            SCRCharaTurnDirectInput(obj, -dist);
        }
    } else if (dldResolve(mot2) == *(char **)anim && *(char *)(GetCharacterClass(obj) + 0x360) != 0) {
        analyzeMotionProperty(obj, *(char **)anim, &len3, 0, 0, 1.0f, *(float *)(anim + 0xC));
        setAttainMotScaleSlowLegCtrlWork(w + 0x3D10, dist / len3);
    }
}
