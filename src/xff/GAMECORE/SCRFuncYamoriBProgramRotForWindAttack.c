typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

extern int DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(void);
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern void analyzeMotionProperty(void *, char *, float *, float *, int, float, float);
extern void setAttainMotScaleSlowLegCtrlWork(char *, float);
extern void _sendProgramRotInput(void *, char *, char *, float);
extern int equipmentInvisibilityCloak(void);
extern void GetMotionNodeQuaternionPos(float *, float *, void *, int, int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern int arrowFilter(void);
extern void updateAimIKWork(void *, void *);
extern char *SkelFocusDef_BOSS_OPT_ATTACK;
extern char gcGlobalVar[];

#ifdef NONMATCHING /* 3 diffs. Wind-attack turn for the Yamori B boss: while its current motion is the given one, scales the leg-slow walk by the AI target's distance in the boss's local space (minus off, over the motion length) and sends a program rotation of deg degrees toward it; unless the cloak is on, aims the IK at the player when the BOSS_OPT_ATTACK node has a clear line. Pinning the matrix-build operands (quat $v0, pos $a0, out $v1) and the matrix-inverse pointer ($v0, returned and passed on to the apply block) gives the Original's registers; remaining: the Original loads pos before forming out (sp+0x10) and rematerialises sp+0x10 into $v0 for the inverse with addiu, where ours copies it from $v1 with daddu. */
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline float vecLength(float *v)
{
    float d;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(v) : "$2");
    return d;
}
static inline void quatPosToMatrix(float *out, float *quat, float *pos)
{
    register float *o __asm__("$3") = out;
    register float *q __asm__("$2") = quat;
    register float *ps __asm__("$4") = pos;
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
                         : : "r"(o), "r"(q) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(o), "r"(ps) : "memory");
}


static inline float *matInverse(float *dst, float *src)
{
    register float *dp __asm__("$2") = dst;
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
                         : "=r"(dp) : "0"(dp), "r"(dp) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
    return dp;
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

void SCRFuncYamoriBProgramRotForWindAttack(void *obj, int b, int c, int d, int e, int f, unsigned int *mot, float deg, float g, float off)
{
    Vec4 m[4];
    VecQ dir;
    char hit[0x50];
    Vec4 pos;
    Vec4 quat;
    float len;
    char *ai;
    char *w;
    char *anim;
    char *lay;

    ai = GetSCRCharaAIWorkPtr();
    w = getSCRDataCtrlWork(obj);
    anim = GetCharacterClass(obj) + 0x1C0;
    lay = GetLayoutClass(obj);
    if (dldResolve(mot) == *(char **)anim) {
        analyzeMotionProperty(obj, *(char **)anim, &len, 0, 0, 1.0f, *(float *)(anim + 0xC));
        quatPosToMatrix(m[0], *(float **)(lay + 0x13C), *(float **)(lay + 0x134));
        { float *mi = matInverse(m[0], m[0]);
        matApply(dir.f, mi, (float *)(ai + 0x41F0)); }
        ((int *)dir.f)[1] = 0;
        setAttainMotScaleSlowLegCtrlWork(w + 0x3D10, (vecLength(dir.f) - off) / len);
        _sendProgramRotInput(obj, w + 0x3D10, ai + 0x41F0, deg * 0.017453293f);
    }
    if (equipmentInvisibilityCloak() == 0) {
        GetMotionNodeQuaternionPos(quat, pos, obj, *(int *)(SkelFocusDef_BOSS_OPT_ATTACK + 8), 1);
        if (ClipCollisionDirectCallBack(hit, pos, *(void **)(*(char **)(w + 0x407C) + 0x134), gcGlobalVar + 0x230, 0, 0, 0, arrowFilter, 0) == 0)
            updateAimIKWork(obj, *(void **)(*(char **)(w + 0x407C) + 0x134));
    }
}
#endif
