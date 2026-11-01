typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern void *isysGetThisSubThread(void);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern void updateScriptDataSystem(void *);
extern void isysRequestDeleteObj(int);
extern void GetMotionNodeQuaternionPos(Vec4 *, Vec4 *, void *, int, int);
extern void StabilizeToYRotQuaternion(Vec4 *);
extern void ForceUnparentLayoutObj(int);
extern void SCRSetLWSGeometryWithZY(int, int, Vec4 *, Vec4 *, Vec4 *);
extern void _SCRStartLWS(int, int, int, int);
extern void scrRunM(int);
extern char *SkelFocusDef_MINOTAUR_SWORD;
extern Vec4 YUnitVector;

static void func_0006B0A8(char *w)
{
    void *th = isysGetThisSubThread();
    Vec4 pos;
    Vec4 dir;
    Vec4 q;

    while (1) {
        void *t = isysGetThisSubThread();
        SCRExecBossPreProcess(*(int *)w);
        CharaCtrlResetAllScriptCtrlStatus(t);
        updateScriptDataSystem(t);
        if (*(int *)(w + 0x4200) != 0) {
            isysRequestDeleteObj(*(int *)(w + 0x41E0));
            GetMotionNodeQuaternionPos(&q, &pos, th, *(int *)(SkelFocusDef_MINOTAUR_SWORD + 8), 1);
            StabilizeToYRotQuaternion(&q);
            __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                                 "vmul.xyzw vf5, vf4, vf4\n"
                                 "vmr32.xyzw vf6, vf4\n"
                                 "vmul.xyzw vf7, vf6, vf4\n"
                                 "vmr32.xyzw vf6, vf6\n"
                                 "vmul.xyzw vf8, vf6, vf4\n"
                                 "vsubx.z vf6, vf0, vf5x\n"
                                 "vsuby.z vf6, vf6, vf5y\n"
                                 "vaddw.y vf6, vf7, vf7w\n"
                                 "vsuby.x vf6, vf8, vf8y\n"
                                 "vsub.w vf6, vf0, vf0\n"
                                 "vadd.w vf5, vf0, vf0\n"
                                 "vmulw.xyz vf6, vf6, vf5w\n"
                                 "vaddw.z vf6, vf6, vf0w\n"
                                 "sqc2 vf6, 0x0(%0)\n"
                                 : : "r"(&dir), "r"(&q) : "memory");
            ForceUnparentLayoutObj(*(int *)(w + 0x41E4));
            SCRSetLWSGeometryWithZY(*(int *)(w + 0x41E4), 0, &pos, &dir, &YUnitVector);
            _SCRStartLWS(*(int *)(w + 0x41E4), -1, 4, 0);
            *(int *)(w + 0x4200) = 0;
        }
        isysGetThisSubThread();
        SCRExecBossPostProcess(*(int *)w);
        scrRunM(1);
    }
}
