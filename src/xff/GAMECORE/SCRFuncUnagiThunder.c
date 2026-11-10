extern char *GetSCRCharaAIWorkPtr(void *);
extern void *GetDamageClass(void *);
extern float getBossPartsLifeRatio(void *, int);
extern int SkelFocusDef_WORM_HEAD2;
extern int SkelFocusDef_WORM_KUBI4;
extern int SkelFocusDef_WORM_MUNE4;
extern void SCRGetCharNodePos(float *, void *, int);
extern char *GetScriptAnimationClass(int);
extern void _SCRStartLWS(int, int, int, int);

void SCRFuncUnagiThunder(void *obj, float limit)
{
    char *w = GetSCRCharaAIWorkPtr(obj);
    float pos[4];

    if (GetDamageClass(obj) != 0) {
        if (getBossPartsLifeRatio(obj, 0x10) == 0.0f)
            *(int *)(w + 0x5A8C) = 1;
        if (getBossPartsLifeRatio(obj, 0x30) == 0.0f)
            *(int *)(w + 0x5A90) = 1;
        if (getBossPartsLifeRatio(obj, 0x40) == 0.0f)
            *(int *)(w + 0x5A94) = 1;
    }
    SCRGetCharNodePos(pos, obj, SkelFocusDef_WORM_HEAD2);
    if (limit < pos[1] || *(int *)(w + 0x5A8C) != 0) {
        if (GetScriptAnimationClass(*(int *)(w + 0x5A80))[0x364] != 1)
            _SCRStartLWS(*(int *)(w + 0x5A80), -1, 1, 0);
    } else {
        if (GetScriptAnimationClass(*(int *)(w + 0x5A80))[0x364] != 5)
            _SCRStartLWS(*(int *)(w + 0x5A80), -1, 5, 0);
    }
    SCRGetCharNodePos(pos, obj, SkelFocusDef_WORM_KUBI4);
    if (limit < pos[1] || *(int *)(w + 0x5A90) != 0) {
        if (GetScriptAnimationClass(*(int *)(w + 0x5A84))[0x364] != 1)
            _SCRStartLWS(*(int *)(w + 0x5A84), -1, 1, 0);
    } else {
        if (GetScriptAnimationClass(*(int *)(w + 0x5A84))[0x364] != 5)
            _SCRStartLWS(*(int *)(w + 0x5A84), -1, 5, 0);
    }
    SCRGetCharNodePos(pos, obj, SkelFocusDef_WORM_MUNE4);
    if (limit < pos[1] || *(int *)(w + 0x5A94) != 0) {
        if (GetScriptAnimationClass(*(int *)(w + 0x5A88))[0x364] != 1)
            _SCRStartLWS(*(int *)(w + 0x5A88), -1, 1, 0);
    } else {
        if (GetScriptAnimationClass(*(int *)(w + 0x5A88))[0x364] != 5)
            _SCRStartLWS(*(int *)(w + 0x5A88), -1, 5, 0);
    }
}
