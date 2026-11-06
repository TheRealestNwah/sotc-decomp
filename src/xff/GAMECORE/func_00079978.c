typedef struct { int obj; int a; int b; int c; int d; unsigned char e; } Slot;
extern char *GetSCRCharaAIWorkPtr(void *);
extern void isysRequestDeleteObj(int);
extern int ScriptAnimationObjDef_HARPOON_START, ScriptAnimationObjDef_HARPOON_LOOP;
extern int SkelFocusDef_PLAYER_HAND_A_R;
extern int _SCRSetupLWSWithTargetNodeParent(int, void *, int);
extern void _SCRStartLWS(int, int, int, char *);
extern void func_00076698(char *);

static void func_00079978(void *chara)
{
    char *w = GetSCRCharaAIWorkPtr(chara);
    int *s = (int *)(w + 0x60);
    if (s[6] != 0) {
        isysRequestDeleteObj(s[6]);
        s[6] = 0;
    }
    if (s[1] != 0) {
        if (*((unsigned char *)s + 0x15) == 0) {
            if (s[3] == 0) {
                isysRequestDeleteObj(s[1]);
            }
        } else {
            isysRequestDeleteObj(s[1]);
        }
        s[1] = 0;
        s[3] = 1;
        *((unsigned char *)s + 0x15) = 0;
    }
    if (s[0] != 0) {
        if (*((unsigned char *)s + 0x14) == 0) {
            if (s[2] == 0) {
                isysRequestDeleteObj(s[0]);
            }
        } else {
            isysRequestDeleteObj(s[0]);
        }
        *((unsigned char *)s + 0x14) = 0;
        s[0] = 0;
        s[2] = 1;
    }
    *(int *)(w + 0x70) = 5;
    *(int *)(w + 0x60) = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_HARPOON_START, chara, SkelFocusDef_PLAYER_HAND_A_R);
    _SCRStartLWS(*(int *)(w + 0x60), -1, 3, w + 0x68);
    func_00076698(w);
}
