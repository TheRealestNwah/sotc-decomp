typedef struct ScriptCtrlDef {
    int pad0;
    int status;
} ScriptCtrlDef;

extern ScriptCtrlDef *ScriptCtrlDef_SCRStopL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRStopR;
extern char *GetSCRCharaAIWorkPtr(void);
extern char *getSCRDataCtrlWork(int);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern int *GetAnimationClass(int);
extern void analyzeMotionProperty(int, int, float, float, int, int, float *);
extern float iosGetATan2fExact(float, float);
extern void CharaCtrlSetScriptCtrlStatus(int, int);

static inline void quatPosMatrix(void *m0, void *q, void *p)
{
    register void *m __asm__("$2") = m0;

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
                         : : "r"(m), "r"(q), "r"(p) : "memory");
}

static inline void invMatrix(void *m)
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

static inline void applyMatrix(void *v0, void *m, void *v1)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "lqc2 vf14, 0x0(%2)\n"
                         "lqc2 vf15, 0x10(%2)\n"
                         "lqc2 vf16, 0x20(%2)\n"
                         "lqc2 vf17, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(v0), "r"(v1), "r"(m) : "memory");
}

static inline void normalize(void *v0, void *v1)
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
                         : : "r"(v0), "r"(v1) : "memory");
}

void SCRFuncBirdInputRotateMotionKey(int chara, float limit)
{
    float mtx[4][4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float prop;
    char *ai;
    char *ctrl;
    char *layout;
    char *cc;
    float ang;
    register void *mA __asm__("$2");

    ai = GetSCRCharaAIWorkPtr();
    ctrl = getSCRDataCtrlWork(chara);
    layout = GetLayoutClass(chara);
    cc = GetCharacterClass(chara);
    if (*(signed char *)(cc + 0x360) != 0) {
        prop = 0.0f;
        analyzeMotionProperty(chara, *GetAnimationClass(chara), 1.0f, 0.0f, 0, 0, &prop);
        if (prop > 0.0f)
            (*(int *)(ai + 0x41D0))--;
        else if (prop < 0.0f)
            (*(int *)(ai + 0x41D0))++;
        if (*(int *)(ai + 0x41D0) < 0)
            *(int *)(ai + 0x41D0) = 0;
        else if (*(int *)(ai + 0x41D0) >= 3)
            *(int *)(ai + 0x41D0) = 2;
    }
    {
    register int one __asm__("$3") = 1;
    mA = mtx;
    *(int *)(ai + 0x41D0) = one;
    }
    quatPosMatrix(mA, cc + 0x470, *(void **)(layout + 0x134));
    invMatrix(mtx);
    applyMatrix(dir, mtx, ctrl + 0x4030);
    dir[1] = 0.0f;
    normalize(dir, dir);
    ang = iosGetATan2fExact(dir[0], dir[2]);
    if (ang > limit * 0.017453293f && *(int *)(ai + 0x41D0) != 0) {
        CharaCtrlSetScriptCtrlStatus(chara, ScriptCtrlDef_SCRStopR->status);
        return;
    }
    if (ang < -(limit * 0.017453293f) && *(int *)(ai + 0x41D0) != 2)
        CharaCtrlSetScriptCtrlStatus(chara, ScriptCtrlDef_SCRStopL->status);
}
