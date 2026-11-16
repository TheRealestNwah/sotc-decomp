extern char *SkelFocusDef_PLAYER_SWORD;
extern char *SkelFocusDef_PLAYER_SWORDTOP;
extern char *ScriptCtrlDef_SCRPlayerAttackSuccess;
extern char *ScriptCtrlDef_SCRPlayerFinishAttack;
extern char *ScriptCtrlDef_SCRPlayerAttackFail;
extern char *ScriptCtrlDef_SCRPlayerAttackFail2;
extern char gcGlobalVar[];
extern void func_0007BC80(void);
extern int _SCRGetCollisionTwoBoneRay(void *, int, int, void *, void *, void (*)(void), int);
extern unsigned long GetGeometryPointerCharColAttr(void *);
extern void *GetGeometryPointerObject(void *);
extern int getSelectWeapon(void);
extern void SendCharaAttackMsg(void *, void *, void *, int, float);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void *SCRGetFirstObj(void *);
extern int SCRGetBossPartsDamageFromColAttr(unsigned long, void *);
extern int SCRGetBackStageBossPartsDamageFromColAttr(unsigned long, void *);
extern void *SCRGetBossWork(void *);
extern int IsBossDeathNextAttack(void *, void *, int, int, int);
extern void CopyGeometryPointer(void *, void *);

static void func_00076A80(void *p, char *work)
{
    char *w = work + 0xA0;
    unsigned long attr;
    void *obj;
    int dmg;
    int dmg2;

    if (*(int *)(work + 0x170))
        *(int *)(work + 0x170) = 0;
    else
        *(long *)(work + 0x178) = 0;
    if (!_SCRGetCollisionTwoBoneRay(w, *(int *)(SkelFocusDef_PLAYER_SWORD + 8), *(int *)(SkelFocusDef_PLAYER_SWORDTOP + 8), gcGlobalVar + 0x230, p, func_0007BC80, 0))
        return;
    attr = GetGeometryPointerCharColAttr(w);
    if ((attr & 8) || (attr & 0x7C00) == 0x2000 || (attr & 0x7C00) == 0x3800 ||
        (attr & (0xFE00UL << 38)) == (0x9000UL << 38)) {
        if (*(int *)(w + 0x40) == 1) {
            obj = GetGeometryPointerObject(w);
            SendCharaAttackMsg(p, obj, w, 0, (float)getSelectWeapon());
            *(int *)(w + 0x40) = 0;
        }
        CharaCtrlSetScriptCtrlStatus(p, *(int *)(ScriptCtrlDef_SCRPlayerAttackSuccess + 4));
        obj = GetGeometryPointerObject(w);
        if (obj != SCRGetFirstObj(gcGlobalVar + 0x2B8))
            return;
        dmg = SCRGetBossPartsDamageFromColAttr(attr, obj);
        dmg2 = SCRGetBackStageBossPartsDamageFromColAttr(attr, obj);
        if (dmg != 0 && IsBossDeathNextAttack(obj, SCRGetBossWork(obj), dmg, dmg2, 0)) {
            CopyGeometryPointer(work + 0xF0, w);
            CharaCtrlSetScriptCtrlStatus(p, *(int *)(ScriptCtrlDef_SCRPlayerFinishAttack + 4));
        }
        return;
    }
    if ((attr & 0xF80000008UL) == (0xE000UL << 19))
        CharaCtrlSetScriptCtrlStatus(p, *(int *)(ScriptCtrlDef_SCRPlayerAttackFail2 + 4));
    CharaCtrlSetScriptCtrlStatus(p, *(int *)(ScriptCtrlDef_SCRPlayerAttackFail + 4));
}
