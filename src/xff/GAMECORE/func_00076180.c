/* w is the AI work block. If the current motion is in the weapon-change list, it reads the pad bits (gcGlobalVar+0x318 next, +0x314 previous), ends nico sight if active, cycles w[0x7C] and plays the cursor sound; otherwise it clears w[0x80] and, when the character is in the list one motion later, copies w[0x7C] into w[0x70] and tail-calls func_0007A8F0 with the old value. The explicit returns after the final calls give the sibling-call `j`. */
extern char gcGlobalVar[];
extern char padManagerData[];
extern char SH_WeaponChangeMotList2DEFAULT[];
extern int *ScriptCtrlDef_SCRPlayerWeaponChangeExec;
extern int SeList_cursor;
extern void *isysGetThisSubThread(void);
extern int *GetAnimationClass(void *);
extern char *GetCharacterClass(void *);
extern int chkMotionList(int, void *);
extern int is_doing_nico_sight_on(void *);
extern void end_nico_sight_on(void *);
extern int selectWeaponNext(int);
extern int selectWeaponBefore(int);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern int sePlaySystemSound(int);
extern void func_0007A8F0(void *, int);

static void func_00076180(char *w)
{
    void *t = isysGetThisSubThread();
    int *anim = GetAnimationClass(t);
    int played;

    if (chkMotionList(anim[0], SH_WeaponChangeMotList2DEFAULT) != 0) {
        int pad;
        int one;
        char *g;

        if (*(int *)(w + 0x80) != 0)
            return;
        g = gcGlobalVar;
        pad = *(int *)(padManagerData + 8);
        one = 1;
        played = 0;
        if (pad & (one << *(int *)(g + 0x318))) {
            char *s = w + 0x190;

            if (is_doing_nico_sight_on(s) == one)
                end_nico_sight_on(s);
            *(int *)(w + 0x7C) = selectWeaponNext(*(int *)(w + 0x7C));
            played = 1;
        } else if (pad & (one << *(int *)(g + 0x314))) {
            char *s = w + 0x190;

            if (is_doing_nico_sight_on(s) == one)
                end_nico_sight_on(s);
            *(int *)(w + 0x7C) = selectWeaponBefore(*(int *)(w + 0x7C));
            played = 1;
        }
        CharaCtrlSetScriptCtrlStatus(t, ScriptCtrlDef_SCRPlayerWeaponChangeExec[1]);
        if (played)
            { sePlaySystemSound(SeList_cursor); return; }
    } else {
        int old;

        *(int *)(w + 0x80) = 0;
        if (GetCharacterClass(t)[0x360] == 0)
            return;
        if (chkMotionList(anim[1], SH_WeaponChangeMotList2DEFAULT) == 0)
            return;
        if (chkMotionList(anim[0], SH_WeaponChangeMotList2DEFAULT) != 0)
            return;
        old = *(int *)(w + 0x70);
        *(int *)(w + 0x70) = *(int *)(w + 0x7C);
        func_0007A8F0(t, old);
        return;
    }
}
