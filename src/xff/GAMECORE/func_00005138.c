#ifdef NONMATCHING
/* 28 diffs, same length (93 words). Whole function is func_00005138 + func_00005278 (spimdisasm split it at the call before the shared epilogue). Remaining: the original reads lc+0x13C in the Force-unparent call's delay slot and keeps lc in $a1 (never in a saved reg); gcc here keeps it in $s0. Constants 100.0f/0.01f load order in the GetClothDynamics call also differs. Permuter (4 workers, 28 min) best 500. Source order of q read before ForceUnparent made it worse (57). */
typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroVector;
extern int D_00179A54;
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern void ForceUnparentLayoutObj(int);
extern void CallLayoutObjDebugResetFunc(int);
extern void ResetCharacterObj(int);
extern void UpdateCharacterClassGeometry(void *);
extern void charrootdyn_getRegularColFinderPosition(void *, void *, void *, void *, float);
extern void UpdateCharacterClassPastGeometry(void *);
extern void SetCharacterObjDemoCutFinishFlag(int, int);
extern void UpdateLayoutClassSimpleGeometry(void *);
extern void GetClothDynamics(float, float, int, int, int);
extern void UpdateLayoutClassPastSimpleGeometry(void *);
extern void SetLayoutClassRootQuaternion(void *, int);
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void reset_game_camera(void *);

static void func_00005138(int obj, int id)
{
    char *lc = GetLayoutClass(id);
    s128 pos;
    int q;
    char *l2;
    char *chara;

    if (lc) {
        pos = **(s128 **)(lc + 0x134);
        ((float *)&pos)[1] += 10.0f;
        ForceUnparentLayoutObj(obj);
        q = *(int *)(lc + 0x13C);
        CallLayoutObjDebugResetFunc(obj);
        ResetCharacterObj(obj);
        l2 = GetLayoutClass(obj);
        if (l2) {
            **(s128 **)(l2 + 0x134) = pos;
            *(s128 *)(l2 + 0x40) = pos;
            *(s128 *)(l2 + 0x30) = ZeroVector;
            chara = GetCharacterClass(obj);
            if (chara) {
                UpdateCharacterClassGeometry(chara);
                charrootdyn_getRegularColFinderPosition(chara + 0x4C0, chara, *(void **)(l2 + 0x13C), *(void **)(l2 + 0x134), 100.0f);
                UpdateCharacterClassPastGeometry(chara);
                SetCharacterObjDemoCutFinishFlag(obj, 1);
            } else {
                UpdateLayoutClassSimpleGeometry(l2);
                GetClothDynamics(0.01f, 100.0f, obj, 1, 0);
                UpdateLayoutClassPastSimpleGeometry(l2);
            }
            SetLayoutClassRootQuaternion(l2, q);
        }
        D_00179A54 += 1;
        reset_game_camera(get_game_camera(get_main_cameraman()));
    }
}
#endif
