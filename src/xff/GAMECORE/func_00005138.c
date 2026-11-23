#ifdef NONMATCHING
/* 9 diffs, same length (93 words). Whole function is func_00005138 + func_00005278 (spimdisasm split it at the call before the shared epilogue). pos is a union so the +10.0f goes through the stack copy after the sq; UpdateCharacterClassGeometry takes 100.0f (loaded before the branch). Remaining: argument setup order for charrootdyn_getRegularColFinderPosition (original loads a2/a3 first, a0 in the delay slot) and GetClothDynamics (original loads 100.0f before 0.01f). */
/* 28 diffs, same length (93 words). Whole function is func_00005138 + func_00005278 (spimdisasm split it at the call before the shared epilogue). Remaining: the original reads lc+0x13C in the Force-unparent call's delay slot and keeps lc in $a1 (never in a saved reg); gcc here keeps it in $s0. Constants 100.0f/0.01f load order in the GetClothDynamics call also differs. Permuter (4 workers, 28 min) best 500. Source order of q read before ForceUnparent made it worse (57). */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern s128 ZeroVector;
extern int D_00179A54;
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern void ForceUnparentLayoutObj(int);
extern void CallLayoutObjDebugResetFunc(int);
extern void ResetCharacterObj(int);
extern void UpdateCharacterClassGeometry(void *, float);
extern void charrootdyn_getRegularColFinderPosition(void *, void *, void *, void *);
extern void UpdateCharacterClassPastGeometry(void *);
extern void SetCharacterObjDemoCutFinishFlag(int, int);
extern void UpdateLayoutClassSimpleGeometry(void *);
extern void GetClothDynamics(int, float, int, int, float);
extern void UpdateLayoutClassPastSimpleGeometry(void *);
extern void SetLayoutClassRootQuaternion(void *, int);
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void reset_game_camera(void *);

static void func_00005138(int obj, int id)
{
    char *lc = GetLayoutClass(id);
    Vec4 pos;
    int q;
    char *l2;
    char *chara;

    if (lc) {
        pos.q = **(s128 **)(lc + 0x134);
        pos.f[1] += 10.0f;
        q = *(int *)(lc + 0x13C);
        ForceUnparentLayoutObj(obj);
        CallLayoutObjDebugResetFunc(obj);
        ResetCharacterObj(obj);
        l2 = GetLayoutClass(obj);
        if (l2) {
            **(s128 **)(l2 + 0x134) = pos.q;
            *(s128 *)(l2 + 0x40) = pos.q;
            *(s128 *)(l2 + 0x30) = ZeroVector;
            chara = GetCharacterClass(obj);
            if (chara) {
                UpdateCharacterClassGeometry(chara, 100.0f);
                charrootdyn_getRegularColFinderPosition(chara + 0x4C0, chara, *(void **)(l2 + 0x13C), *(void **)(l2 + 0x134));
                UpdateCharacterClassPastGeometry(chara);
                SetCharacterObjDemoCutFinishFlag(obj, 1);
            } else {
                UpdateLayoutClassSimpleGeometry(l2);
                GetClothDynamics(obj, 0.01f, 1, 0, 100.0f);
                UpdateLayoutClassPastSimpleGeometry(l2);
            }
            SetLayoutClassRootQuaternion(l2, q);
        }
        D_00179A54 += 1;
        reset_game_camera(get_game_camera(get_main_cameraman()));
    }
}
#endif
