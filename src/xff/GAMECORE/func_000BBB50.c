/* Parked draft: main script loop of the snake (bag) boss's body. Each frame it resets the script
   control, clears the front/centre/back flags at +0x5A80/84/88, then walks the character's parts
   (stride 0x80): a deflating motion (F/M/B_DEFLATE0/1) of a part starts the matching SCRSnakeFade
   control, and while the damage class is in state 1/2/4 a *_DEFLATE_SWELLING part hit at the right
   attack point (0x20 front, 0x180 centre, 0x190 back) plays the fade effect. Never returns (loops on
   scrRunM). Written from the m2c draft; not yet compared closely. */
#ifdef NONMATCHING
typedef struct {
    char pad0[4];
    int ctrl;
} ScriptCtrlDef;

extern int MotionKind_SNAKE_C_B_DEFLATE0;
extern int MotionKind_SNAKE_C_B_DEFLATE1;
extern int MotionKind_SNAKE_C_B_DEFLATE_SWELLING;
extern int MotionKind_SNAKE_C_F_DEFLATE0;
extern int MotionKind_SNAKE_C_F_DEFLATE1;
extern int MotionKind_SNAKE_C_F_DEFLATE_SWELLING;
extern int MotionKind_SNAKE_C_M_DEFLATE0;
extern int MotionKind_SNAKE_C_M_DEFLATE1;
extern int MotionKind_SNAKE_C_M_DEFLATE_SWELLING;
extern int ScriptAnimationObjDef_SNAKE_BAG_FADE_EFF;
extern ScriptCtrlDef *ScriptCtrlDef_SCRSnakeFadeBack;
extern ScriptCtrlDef *ScriptCtrlDef_SCRSnakeFadeCenter;
extern ScriptCtrlDef *ScriptCtrlDef_SCRSnakeFadeFront;
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern char *GetCharacterClass(int);
extern char *GetDamageClass(int);
extern void SCRExecBossPostProcess(int);
extern void SCRExecBossPreProcess(int);
extern void _SCRPlayLWSWithTargetAttackedPoint(int, int);
extern void func_000BBED8(int);
extern int isysGetThisSubThread(void);
extern int nico_GetCharacterAttackedGPAttr(int, int);
extern void scrRunM(int);
extern void updateScriptDataSystem(int);

static void func_000BBB50(char *boss)
{
    int self = isysGetThisSubThread();

    for (;;) {
        int i = 0;
        int t = isysGetThisSubThread();
        char *part;
        char *damage;

        SCRExecBossPreProcess(*(int *)boss);
        CharaCtrlResetAllScriptCtrlStatus(t);
        updateScriptDataSystem(t);
        part = *(char **)(GetCharacterClass(self) + 0x30C);
        *(int *)(boss + 0x5A80) = 0;
        *(int *)(boss + 0x5A84) = 0;
        *(int *)(boss + 0x5A88) = 0;
        damage = GetDamageClass(self);
        while (i < *(int *)(GetCharacterClass(self) + 0x3FC)) {
            if (*(int *)(part + 0x44) != -2) {
                if (*(int *)(boss + 0x5A8C) == 0) {
                    int m = *(int *)(part + 4);

                    if (MotionKind_SNAKE_C_F_DEFLATE0 == m || MotionKind_SNAKE_C_F_DEFLATE1 == m) {
                        *(int *)(boss + 0x5A80) = 1;
                        CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeFront->ctrl);
                    } else if (MotionKind_SNAKE_C_M_DEFLATE0 == m || MotionKind_SNAKE_C_M_DEFLATE1 == m) {
                        *(int *)(boss + 0x5A84) = 1;
                        CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeCenter->ctrl);
                    } else if (MotionKind_SNAKE_C_B_DEFLATE0 == m || MotionKind_SNAKE_C_B_DEFLATE1 == m) {
                        *(int *)(boss + 0x5A88) = 1;
                        CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeBack->ctrl);
                    }
                }
                if (damage != 0) {
                    int st = *(int *)(damage + 0x60);

                    if (st == 1 || st == 4 || st == 2) {
                        int m = *(int *)(part + 4);

                        if (MotionKind_SNAKE_C_F_DEFLATE_SWELLING == m) {
                            if (nico_GetCharacterAttackedGPAttr(self, 0x3F0) == 0x20) {
                                CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeFront->ctrl);
                                _SCRPlayLWSWithTargetAttackedPoint(ScriptAnimationObjDef_SNAKE_BAG_FADE_EFF, self);
                            }
                        } else if (MotionKind_SNAKE_C_M_DEFLATE_SWELLING == m) {
                            if (nico_GetCharacterAttackedGPAttr(self, 0x3F0) == 0x180) {
                                CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeCenter->ctrl);
                                _SCRPlayLWSWithTargetAttackedPoint(ScriptAnimationObjDef_SNAKE_BAG_FADE_EFF, self);
                            }
                        } else if (MotionKind_SNAKE_C_B_DEFLATE_SWELLING == m &&
                                   nico_GetCharacterAttackedGPAttr(self, 0x3F0) == 0x190) {
                            CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeBack->ctrl);
                            _SCRPlayLWSWithTargetAttackedPoint(ScriptAnimationObjDef_SNAKE_BAG_FADE_EFF, self);
                        }
                    }
                }
            }
            i++;
            part += 0x80;
        }
        *(int *)(boss + 0x5A8C) = 0;
        func_000BBED8(self);
        isysGetThisSubThread();
        SCRExecBossPostProcess(*(int *)boss);
        scrRunM(1);
    }
}
#endif
