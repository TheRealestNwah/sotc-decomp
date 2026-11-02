extern int *DldSysUndefSymbol;
extern int SH_ScriptRequestEffectDefPOSEIDON_HIT[];
extern int ScriptRequestEffectDef_COM_TORCHHIT;
extern int ScriptRequestEffectDef_POSE_ICOSWORDHIT_M;
extern int ScriptRequestEffectDef_ICOSWORDHIT_M;
extern int ScriptRequestEffectDef_POSE_SWORDHIT_M;
extern int ScriptRequestEffectDef_SWORDHIT_M;
extern char *GetSCRCharaAIWorkPtr(void *);
extern long nico_GetGeometryPointerAttr(char *);
extern void ExecEff(int, int, void *, int, void *);

static void T_0007A038(void *o)
{
    char *w = GetSCRCharaAIWorkPtr(o);
    char *g = w + 0xA0;

    *(int *)(w + 0x170) = 1;
    *(long *)(w + 0x178) = nico_GetGeometryPointerAttr(g);
    if (*(int *)(w + 0x70) == 9) {
        ExecEff(ScriptRequestEffectDef_COM_TORCHHIT, 0, o, 0, g);
    } else if (*(int *)(w + 0x70) == 3) {
        if (DldSysUndefSymbol != SH_ScriptRequestEffectDefPOSEIDON_HIT) {
            ExecEff(ScriptRequestEffectDef_POSE_ICOSWORDHIT_M, 0, o, 0, g);
        } else {
            ExecEff(ScriptRequestEffectDef_ICOSWORDHIT_M, 0, o, 0, g);
        }
    } else {
        if (DldSysUndefSymbol != SH_ScriptRequestEffectDefPOSEIDON_HIT) {
            ExecEff(ScriptRequestEffectDef_POSE_SWORDHIT_M, 0, o, 0, g);
        } else {
            ExecEff(ScriptRequestEffectDef_SWORDHIT_M, 0, o, 0, g);
        }
    }
}
