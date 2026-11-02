extern void *isysGetThisSubThread(void);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern void updateScriptDataSystem(void *);
extern char *GetLayoutClass(void *);
extern char *getSCRDataCtrlWork(void *);
extern void scrRunM(int);

static void func_00034C98(char *w)
{
    void *th = isysGetThisSubThread();

    while (1) {
        void *t = isysGetThisSubThread();
        char *layout;
        char *other;
        float d;

        SCRExecBossPreProcess(*(int *)w);
        CharaCtrlResetAllScriptCtrlStatus(t);
        updateScriptDataSystem(t);
        *(float *)(w + 0x41D8) = *(float *)(w + 0x41D4);
        layout = GetLayoutClass(th);
        other = *(char **)(getSCRDataCtrlWork(th) + 0x407C);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "vmul.xz vf7, vf7, vf7\n"
                             "vaddz.x vf7, vf7, vf7z\n"
                             "vsqrt Q, vf7x\n"
                             "vwaitq\n"
                             "cfc2 $2, $vi22\n"
                             "mtc1 $2, %0\n"
                             : "=f"(d) : "r"(*(float **)(layout + 0x134)), "r"(*(float **)(other + 0x134))
                             : "$2");
        *(float *)(w + 0x41D4) = d;
        isysGetThisSubThread();
        SCRExecBossPostProcess(*(int *)w);
        scrRunM(1);
    }
}
