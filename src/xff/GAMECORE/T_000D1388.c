extern char gcGlobalVar[];
static const union {
    int i;
    float f;
} RO_00180D90 = { 0x7FFFFFFF };
extern void *isysGetThisSubThread(void);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern void updateScriptDataSystem(void *);
extern int *GetDamageClass(void *);
extern int nico_GetCharacterAttackedGPAttr(void *, int);
extern void scrRunM(int);

static void T_000D1388(char *w)
{
    void *th = isysGetThisSubThread();
    char *g = gcGlobalVar;

    while (1) {
        void *cur = isysGetThisSubThread();
        int *d;

        SCRExecBossPreProcess(*(int *)w);
        CharaCtrlResetAllScriptCtrlStatus(cur);
        updateScriptDataSystem(cur);
        d = GetDamageClass(th);
        if (d != 0 && d[0] == 3
            && (nico_GetCharacterAttackedGPAttr(th, 0x3F0) == 0x160
                || nico_GetCharacterAttackedGPAttr(th, 0x3F0) == 0x180
                || nico_GetCharacterAttackedGPAttr(th, 0x3F0) == 0x170
                || nico_GetCharacterAttackedGPAttr(th, 0x3F0) == 0x190)
            && ((unsigned int)(d[0x18] - 1) < 2 || d[0x18] == 4)) {
            *(int *)(w + 0x41E4) = 0;
            *(int *)(w + 0x41E0) += 1;
        }
        if (*(int *)(w + 0x41E0) > 0)
            *(float *)(w + 0x41E4) += *(float *)(g + 0x180);
        if (*(float *)(w + 0x41E8) < *(float *)(w + 0x41E4)) {
            *(float *)(w + 0x41E4) = RO_00180D90.f;
            *(int *)(w + 0x41E0) = 0;
        }
        isysGetThisSubThread();
        SCRExecBossPostProcess(*(int *)w);
        scrRunM(1);
    }
}
