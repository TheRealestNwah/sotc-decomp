extern char *GetSCRCharaAIWorkPtr(void);
extern int ScriptAnimationObjDef_TTS_PLS_CHARGE;
extern int SkelFocusDef_BOSS_HEAD;
extern int _SCRSetupLWSWithTargetNodeParent(int, void *, int);
extern void _SCRStartLWS(int, int, int, int);

static void T_000CB538(void *p)
{
    char *w = GetSCRCharaAIWorkPtr();
    int l = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_TTS_PLS_CHARGE, p, SkelFocusDef_BOSS_HEAD);

    *(int *)(w + 0x41D0) = l;
    _SCRStartLWS(l, -1, 3, 0);
}
