extern int *DldSysUndefSymbol;
extern int SH_ScriptRequestEffectDefPOSEIDON_HIT[];
extern int ScriptRequestEffectDef_POSE_ICOSWORDHIT_DIVE;
extern int ScriptRequestEffectDef_ICOSWORDHIT_DIVE;
extern int ScriptRequestEffectDef_POSE_SWORDHIT_DIVE;
extern int ScriptRequestEffectDef_SWORDHIT_DIVE;
extern char *GetSCRCharaAIWorkPtr(void *);
extern void ExecEff(int, int, void *, int, void *);

static void T_0007A2F8(void *o)
{
    char *w = GetSCRCharaAIWorkPtr(o);

    if (*(int *)(w + 0x70) == 3) {
        if (DldSysUndefSymbol != SH_ScriptRequestEffectDefPOSEIDON_HIT) {
            ExecEff(ScriptRequestEffectDef_POSE_ICOSWORDHIT_DIVE, 0, o, 0, w + 0xA0);
        } else {
            ExecEff(ScriptRequestEffectDef_ICOSWORDHIT_DIVE, 0, o, 0, w + 0xA0);
        }
    } else {
        if (DldSysUndefSymbol != SH_ScriptRequestEffectDefPOSEIDON_HIT) {
            ExecEff(ScriptRequestEffectDef_POSE_SWORDHIT_DIVE, 0, o, 0, w + 0xA0);
        } else {
            ExecEff(ScriptRequestEffectDef_SWORDHIT_DIVE, 0, o, 0, w + 0xA0);
        }
    }
}
