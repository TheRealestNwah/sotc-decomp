extern char *GetCharacterClass(int);
extern float SCRGetXZAngle(float *);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern float YUnitVector[4];
extern int *ScriptCtrlDef_SCRYamori2FallUpward;
extern int *ScriptCtrlDef_SCRYamori2FallUpwardLower;
extern int *ScriptCtrlDef_SCRYamori2FallLeftwardUpper;
extern int *ScriptCtrlDef_SCRYamori2FallRightwardUpper;
extern int *ScriptCtrlDef_SCRYamori2FallLeftward;
extern int *ScriptCtrlDef_SCRYamori2FallRightward;
extern int *ScriptCtrlDef_SCRYamori2FallLeftwardLower;
extern int *ScriptCtrlDef_SCRYamori2FallRightwardLower;
extern int *ScriptCtrlDef_SCRYamori2FallDownward;
extern int *ScriptCtrlDef_SCRYamori2FallDownwardLower;

static inline void quat_to_matrix(float *m, float *q)
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
                         : : "r"(m), "r"(q) : "memory");
}

static inline void set_unit_w(float *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(v));
}

static inline void inverse_matrix(float *m)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%0)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%0)\n"
                         "lq $9, 0x10(%0)\n"
                         "lq $10, 0x20(%0)\n"
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
                         : : "r"(m) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

static inline void apply_matrix(float *out, float *m, float *v)
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

static inline void normalize(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v));
}

void SCRFuncYamoriBSendFallKey(int obj)
{
    float v[4] __attribute__((aligned(16)));
    float m[16] __attribute__((aligned(16)));
    char *cc = GetCharacterClass(obj);
    float a;
    int *def;

    quat_to_matrix(m, (float *)(cc + 0x470));
    set_unit_w(&m[12]);
    inverse_matrix(m);
    apply_matrix(v, m, YUnitVector);
    v[1] = 0.0f;
    normalize(v);
    a = SCRGetXZAngle(v) * 57.29578f;
    if (__builtin_fabsf(a) <= 22.5f) {
        if ((*(long long *)(GetCharacterClass(obj) + 0x690) & 0x1E00000) == 0x600000)
            CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRYamori2FallUpwardLower[1]);
        else
            CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRYamori2FallUpward[1]);
    } else if (22.5f <= a && a <= 67.5f) {
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRYamori2FallLeftwardUpper[1]);
    } else if (a <= -22.5f && -67.5f <= a) {
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRYamori2FallRightwardUpper[1]);
    } else if (67.5f <= a && a <= 112.5f) {
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRYamori2FallLeftward[1]);
    } else if (a <= -67.5f && -112.5f <= a) {
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRYamori2FallRightward[1]);
    } else if (112.5f <= a && a <= 157.5f) {
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRYamori2FallLeftwardLower[1]);
    } else if (a <= -112.5f && -157.5f <= a) {
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRYamori2FallRightwardLower[1]);
    } else {
        if ((*(long long *)(GetCharacterClass(obj) + 0x690) & 0x1E00000) == 0x600000)
            CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRYamori2FallDownwardLower[1]);
        else
            CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRYamori2FallDownward[1]);
    }
}
