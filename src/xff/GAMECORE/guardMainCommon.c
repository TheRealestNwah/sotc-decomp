/* Parked attempt: 4 diffs (lw $a1 load order around the quaternion asm, and $v1 copied from $a0 instead of rematerialized). */
#ifdef NONMATCHING
typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

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
                         "lqc2 vf4, 0x0(%2)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(quat), "r"(pos) : "memory");
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

extern char *GameObject_SHAMAN_P;
extern char *GameObject_DORMIN_P;
extern int MotionKind_SHAMAN_WALK;
extern int MotionKind_SHAMAN_RUN;
extern int MotionKind_SHAMAN_SPELL_START;
extern int MotionKind_SHAMAN_SPELL_LOOP;
extern int MotionKind_SHAMAN_SPELL_END;
extern char *ScriptCtrlDef_SCRGoR;
extern char *ScriptCtrlDef_SCRGoL;
extern char *ScriptCtrlDef_SCRAccel;
extern char gcGlobalVar[];
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern int *GetAnimationClass(int);
extern void setAttainModePathWork(void *, int);
extern void setDashHumanCtrlWork(void *, int);
extern void iosRotMatrixY(float *, float);
extern void setAttainmentPos(void *, float *);
extern int getWayFinish(void *);
extern float iosGetATan2fExact(float, float);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern float calcProgRotRatio(float, float, float, float, float);
extern void SCRCharaTurnDirectInput(int, float);
extern void _setExecBaseMoveWork(void *, int);

static inline float distXZ(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void vecSub(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

void guardMainCommon(int obj, int *flag, void *path, void *hc, char *ctrl, float yaw, float scale)
{
    int sh = *(int *)(GameObject_SHAMAN_P + 8);
    char *ls = GetLayoutClass(sh);
    char *ld = GetLayoutClass(*(int *)(GameObject_DORMIN_P + 8));
    char *lo = GetLayoutClass(obj);
    VecQ d;
    Vec4 rm[4];
    Vec4 m[4];
    VecQ r;
    float a;
    float t;
    char *an;

    *(float *)(GetCharacterClass(obj) + 0x524) = 1.0f;
    if (MotionKind_SHAMAN_WALK == *GetAnimationClass(sh) || MotionKind_SHAMAN_RUN == *GetAnimationClass(sh)) {
        if (distXZ(*(float **)(ls + 0x134), *(float **)(lo + 0x134)) < 3.0f)
            *(float *)(GetCharacterClass(obj) + 0x524) = 0.7f;
        setAttainModePathWork(path, 1);
    } else {
        setAttainModePathWork(path, 0);
    }
    if (distXZ(*(float **)(lo + 0x134), *(float **)(ls + 0x134)) > 5.0f)
        setDashHumanCtrlWork(hc, 1);
    else
        setDashHumanCtrlWork(hc, 0);
    vecSub(d.f, *(float **)(ld + 0x134), *(float **)(ls + 0x134));
    d.f[1] = 0;
    vecNormalize(d.f, d.f);
    d.f[3] = 1.0f;
    iosRotMatrixY(rm[0], yaw);
    matApply(d.f, rm[0], d.f);
    vecScale(d.f, d.f, scale);
    vecAdd(d.f, d.f, *(float **)(ls + 0x134));
    d.f[3] = 1.0f;
    setAttainmentPos(path, d.f);
    if (MotionKind_SHAMAN_SPELL_START == *GetAnimationClass(sh) || MotionKind_SHAMAN_SPELL_LOOP == *GetAnimationClass(sh) ||
        MotionKind_SHAMAN_SPELL_END == *GetAnimationClass(sh)) {
        if (*flag == 0)
            *flag = getWayFinish(path);
        if (*flag != 0) {
        {
            register float *po __asm__("$4") = m[0];
            register float *pq __asm__("$2") = *(float **)(lo + 0x13C);
            register float *pp __asm__("$5") = *(float **)(lo + 0x134);

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
                         : : "r"(po), "r"(pq), "r"(pp) : "memory");
        }
        {
            register float *pi __asm__("$3") = m[0];

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
                         : : "r"(pi), "r"(pi) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
            matApply(r.f, pi, *(float **)(ld + 0x134));
        }
        r.f[1] = 0;
        vecNormalize(r.f, r.f);
        a = iosGetATan2fExact(r.f[0], r.f[2]);
        if (__builtin_fabsf(a) < 0.087266462f) {
            if (ctrl != 0)
                CharaCtrlSetScriptCtrlStatus(obj, *(int *)(ctrl + 4));
        } else {
            an = *(char **)GetAnimationClass(obj);
            t = calcProgRotRatio(a, *(int *)(an + 0x74) * 0.017453293f, *(float *)(gcGlobalVar + 0x190),
                                 *(float *)(GetCharacterClass(obj) + 0x72C) * 0.017453293f, *(float *)(an + 0x78));
            if (a > 0.0f) {
                CharaCtrlSetScriptCtrlStatus(obj, *(int *)(ScriptCtrlDef_SCRGoR + 4));
                SCRCharaTurnDirectInput(obj, t);
            } else if (a < 0.0f) {
                CharaCtrlSetScriptCtrlStatus(obj, *(int *)(ScriptCtrlDef_SCRGoL + 4));
                SCRCharaTurnDirectInput(obj, -t);
            }
            CharaCtrlSetScriptCtrlStatus(obj, *(int *)(ScriptCtrlDef_SCRAccel + 4));
        }
        _setExecBaseMoveWork(hc, 0);
        } else {
            _setExecBaseMoveWork(hc, 1);
        }
    } else {
        _setExecBaseMoveWork(hc, 1);
        *flag = 0;
    }
}
#endif
