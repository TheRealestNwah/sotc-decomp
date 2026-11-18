extern int *DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, void *, void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern char *GameObject_CANOSSA_ENV;
extern char *ScriptCtrlDef_SCRCanossaWallBreak;
extern char *SkelFocusDef_MINO_B_Opt_HandR_Front;
extern char *SkelFocusDef_MINO_B_Opt_HandR_Back;
extern char *SkelFocusDef_MINO_B_Opt_HandR_Right;
extern char *SkelFocusDef_MINO_B_Opt_HandL_Front;
extern char *SkelFocusDef_MINO_B_Opt_HandL_Back;
extern char *SkelFocusDef_MINO_B_Opt_HandL_Left;
extern char *SkelFocusDef_MINO_B_Opt_FootR_Front;
extern char *SkelFocusDef_MINO_B_Opt_FootR_Back;
extern char *SkelFocusDef_MINO_B_Opt_FootR_Right;
extern char *SkelFocusDef_MINO_B_Opt_FootL_Front;
extern char *SkelFocusDef_MINO_B_Opt_FootL_Back;
extern char *SkelFocusDef_MINO_B_Opt_FootL_Left;

static inline char *dldData(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

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
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

void SCRFuncMinoBCanossaWallBreak(void *self, int a1, int a2, int a3, int a4, unsigned int *h, void *vh,
                                  unsigned int *bone, float dist)
{
    char buf[0x60];
    float q[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    char *work = GetSCRCharaAIWorkPtr(self);
    char *obj = dldData(h);
    char *lay;
    int i;

    if (*(int *)(work + 0x41E0) < 4 && obj != 0 && *(void **)(obj + 8) != 0 && GetCharacterClass(*(void **)(obj + 8)) != 0) {
        char **slot = (char **)(GetCharacterClass(*(void **)(obj + 8)) + 0x1C0);

        if (dldResolve(bone) == *slot) {
            bone = 0;
            lay = GetLayoutClass(*(void **)(obj + 8));
            if (__builtin_fabsf(distXZ(*(float **)(lay + 0x134), *(float **)(GetLayoutClass(self) + 0x134))) < dist) {
                for (i = 0; i < 12; i++) {
                    switch (i) {
                    case 0:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandR_Front + 8), 1);
                        break;
                    case 1:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandR_Back + 8), 1);
                        break;
                    case 2:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandR_Right + 8), 1);
                        break;
                    case 3:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandL_Front + 8), 1);
                        break;
                    case 4:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandL_Back + 8), 1);
                        break;
                    case 5:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandL_Left + 8), 1);
                        break;
                    case 6:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootR_Front + 8), 1);
                        break;
                    case 7:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootR_Back + 8), 1);
                        break;
                    case 8:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootR_Right + 8), 1);
                        break;
                    case 9:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootL_Front + 8), 1);
                        break;
                    case 10:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootL_Back + 8), 1);
                        break;
                    case 11:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootL_Left + 8), 1);
                        break;
                    }
                    if (*(void **)(GameObject_CANOSSA_ENV + 8) != 0)
                        bone = (unsigned int *)CheckPositionInsideOfJudgeVolumeObject(buf, *(void **)(GameObject_CANOSSA_ENV + 8), vh, pos);
                    if (bone) {
                        CharaCtrlSetScriptCtrlStatus(*(void **)(obj + 8), *(int *)(ScriptCtrlDef_SCRCanossaWallBreak + 4));
                        (*(int *)(work + 0x41E0))++;
                        break;
                    }
                }
            }
        }
    }
}
