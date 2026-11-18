/* Scripted turn input: when the character's turn setup (cc+0x1C0, int +0x74 degrees) is nonzero and the work struct's +4 flag is clear, builds the layout's matrix (quaternion +0x13C, position +0x134), inverts it in place, transforms the input vector, flattens y, normalises, takes atan2(x, z) and asks calcProgRotRatio for the turn rate; with a nonzero rate and |angle| above the threshold it switches to ScriptCtrlDef_SCRGoR / SCRGoL and feeds SCRCharaTurnDirectInput (+/- rate). The register pins give the Original's allocation (zero in $f1, layout in a1, position and quaternion loaded into a0 and v0, matrix in v1). */
typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

extern char gcGlobalVar[];
extern int *ScriptCtrlDef_SCRGoR;
extern int *ScriptCtrlDef_SCRGoL;
extern char *GetCharacterClass(void);
extern char *GetLayoutClass(int);
extern float iosGetATan2fExact(float, float);
extern float calcProgRotRatio(float, float, float, float, float);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern void SCRCharaTurnDirectInput(int, float);

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
    register float *q asm("$2") = quat;
    register float *o asm("$3") = out;
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%0)\n"
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
                         "sqc2 vf14, 0x0(%1)\n"
                         "sqc2 vf15, 0x10(%1)\n"
                         "sqc2 vf16, 0x20(%1)\n"
                         : : "r"(q), "r"(o) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(o), "r"(pos) : "memory");
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

int _sendProgramRotInput(int obj, char *w, float *vin, float thr)
{
    Vec4 m[4];
    Vec4 v;
    char *cc;
    register char *lay asm("$5");
    char *p;
    float ang;
    float r;

    cc = GetCharacterClass();
    lay = GetLayoutClass(obj);
    p = *(char **)(cc + 0x1C0);
    {
        register float z asm("$f1") = 0.0f;

        if ((float)*(int *)(p + 0x74) == z)
            return 0;
    }
    if (*(int *)(w + 4) != 0)
        return 0;
    { register float *pp asm("$4") = *(float **)(lay + 0x134); register float *qq asm("$2") = *(float **)(lay + 0x13C); quatPosToMatrix(m[0], qq, pp); }
    matInverse(m[0], m[0]);
    matApply(v, m[0], vin);
    *(int *)&v[1] = 0;
    vecNormalize(v, v);
    ang = iosGetATan2fExact(v[0], v[2]);
    r = calcProgRotRatio(ang, (float)*(int *)(p + 0x74) * 0.017453294f, *(float *)(gcGlobalVar + 0x190), *(float *)(cc + 0x72C) * 0.017453294f, *(float *)(p + 0x78));
    if (r == 0.0f)
        return 1;
    if (thr < ang) {
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRGoR[1]);
        SCRCharaTurnDirectInput(obj, r);
    } else if (ang < -thr) {
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRGoL[1]);
        SCRCharaTurnDirectInput(obj, -r);
    }
    return 1;
}
