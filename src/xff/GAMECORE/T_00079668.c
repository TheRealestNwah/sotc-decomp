typedef struct {
    void *a;
    void *b;
    int a_kept;
    int b_kept;
    char pad10[0x4];
    unsigned char a_own;
    unsigned char b_own;
    char pad16[0x2];
    void *c;
} HarpoonLws;

extern int SkelFocusDef_PLAYER_HAND_A_R;
extern int SkelFocusDef_PLAYER_HAND_A_L;
extern int ScriptAnimationObjDef_ARROW_LOOP;
extern int ScriptAnimationObjDef_ARROW_SOUND_LOOP;
extern int ScriptAnimationObjDef_ARROW_EXP_LOOP;
extern int ScriptAnimationObjDef_BOW_LOOP;
extern char *GetSCRCharaAIWorkPtr(void *);
extern void isysRequestDeleteObj(void *);
extern void *_SCRSetupLWSWithTargetNodeParent(int, void *, int);
extern void _SCRStartLWS(void *, int, int, void *);
extern void func_00076698(char *);

static void T_00079668(void *obj)
{
    char *w = GetSCRCharaAIWorkPtr(obj);
    HarpoonLws *h = (HarpoonLws *)(w + 0x60);

    if (h->c != 0) {
        isysRequestDeleteObj(h->c);
        h->c = 0;
    }
    if (h->b != 0) {
        if (h->b_own == 0) {
            if (h->b_kept == 0)
                isysRequestDeleteObj(h->b);
        } else {
            isysRequestDeleteObj(h->b);
        }
        h->b = 0;
        h->b_kept = 1;
        h->b_own = 0;
    }
    if (h->a != 0) {
        if (h->a_own == 0) {
            if (h->a_kept == 0)
                isysRequestDeleteObj(h->a);
        } else {
            isysRequestDeleteObj(h->a);
        }
        h->a = 0;
        h->a_kept = 1;
        h->a_own = 0;
    }
    if (*(int *)(w + 0x70) == 4)
        *(void **)(w + 0x60) = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_ARROW_LOOP, obj, SkelFocusDef_PLAYER_HAND_A_R);
    else if (*(int *)(w + 0x70) == 6)
        *(void **)(w + 0x60) = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_ARROW_SOUND_LOOP, obj, SkelFocusDef_PLAYER_HAND_A_R);
    else
        *(void **)(w + 0x60) = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_ARROW_EXP_LOOP, obj, SkelFocusDef_PLAYER_HAND_A_R);
    *(void **)(w + 0x64) = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_BOW_LOOP, obj, SkelFocusDef_PLAYER_HAND_A_L);
    _SCRStartLWS(*(void **)(w + 0x60), -1, 5, w + 0x68);
    _SCRStartLWS(*(void **)(w + 0x64), -1, 5, w + 0x6C);
    w[0x74] = 1;
    w[0x75] = 1;
    func_00076698(w);
}
