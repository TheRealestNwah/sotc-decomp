extern char *GetSCRCharaAIWorkPtr(void *);
extern int _gameFlagChk(int);

void SCRFuncKameFallPatienceCunterInit(void *a, float base, float add)
{
    char *ai = GetSCRCharaAIWorkPtr(a);

    *(float *)(ai + 0x41C0) = base;
    if (_gameFlagChk(0x117) || _gameFlagChk(0x118) || _gameFlagChk(0x119) || _gameFlagChk(0x11A))
        *(float *)(ai + 0x41C0) += add;
}
