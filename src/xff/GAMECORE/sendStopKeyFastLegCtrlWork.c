/* Sibling of _sendProgramRotInput: direction from the character's position (cc+0x134 pointer) to the target, normalised with w = 1.0, transformed by the inverse of the character's quaternion matrix (cc+0x470, rows only, identity translation row stored from vf0), atan2(x, z) as the turn angle; when the character's mode (cc+0x750) equals w+0x20 it refreshes the motion ratio at w+0x110 through calcNextMotRatio (only while it still holds the sentinel RO_001814B8, an all-ones word compared as a float), otherwise switches to SCRStop and then SCRStopR / SCRStopL by angle versus the threshold (one shared call) and re-arms w+0x110 with the sentinel. w is pinned to $s2 and the shared call's obj to $a0 so each arm sets $a0 like the Original; the identity-row store has no "memory" clobber so the matrix address is rebuilt from $sp after it. */
typedef float Vec4[4] __attribute__((aligned(16)));

extern int *ScriptCtrlDef_SCRStop;
extern int *ScriptCtrlDef_SCRStopL;
extern int *ScriptCtrlDef_SCRStopR;
extern char *GetCharacterClass(void);
extern float iosGetATan2fExact(float, float);
extern float calcNextMotRatio(int, void *, float, float);
extern void CharaCtrlSetScriptCtrlStatus(int, int);

static const int RO_001814B8 = -1;
#define RO_F (*(float *)&RO_001814B8)

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

static inline void quatToMatrix3(float *out, float *quat)
{
    register float *o asm("$4") = out;
    register float *q asm("$2") = quat;
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

int sendStopKeyFastLegCtrlWork(int obj, char *w0, char *target, float thr)
{
    register char *w asm("$18") = w0;
    Vec4 v;
    Vec4 m[4];
    char *cc;
    float ang;
    char *cr;

    cc = GetCharacterClass();
    cr = cc + 0x1C0;
    if (*(int *)(w + 4) != 0)
        return 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(v), "r"(target), "r"(*(char **)(cc + 0x134)) : "memory");
    vecNormalize(v, v);
    v[3] = 1.0f;
    quatToMatrix3(m[0], (float *)(cc + 0x470));
    { register float *p3 asm("$3") = m[3]; __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(p3)); }
    { register float *mm asm("$2") = m[0]; __asm__("" : "+r"(mm)); matInverse(mm, mm); matApply(v, mm, v); }
    ang = iosGetATan2fExact(v[0], v[2]);
    if (*(int *)(cc + 0x750) == *(int *)(w + 0x20)) {
        if (*(float *)(w + 0x110) == RO_F)
            *(float *)(w + 0x110) = calcNextMotRatio(obj, cr, ang, *(float *)(cc + 0x574));
        return 1;
    }
    CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRStop[1]);
    {
        register int a asm("$4");
        register int *s __asm__("$2");

        if (thr < ang) {
            a = obj;
            s = ScriptCtrlDef_SCRStopR;
        } else if (ang < -thr) {
            a = obj;
            s = ScriptCtrlDef_SCRStopL;
        } else
            return 0;
        CharaCtrlSetScriptCtrlStatus(a, s[1]);
    }
    *(float *)(w + 0x110) = RO_F;
    __asm__ __volatile__("");
    return 0;
}
