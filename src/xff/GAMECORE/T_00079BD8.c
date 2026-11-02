extern char *SkelFocusDef_PLAYER_SWORD;
extern char *SkelFocusDef_PLAYER_SWORDTOP;
extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(void *);
extern void _SCRGetCollisionTwoBoneRay(char *, int, int, void *, void *, void *, int);
extern int GetGeometryPointerCharColAttr(char *);
extern void resetAttackPower(void);
extern void *GetGeometryPointerObject(char *);
extern int getSelectWeapon(void);
extern void SendCharaAttackMsg(void *, void *, char *, int, float);
extern void func_0007BC80(void);

static void T_00079BD8(void *obj)
{
    char *g = GetSCRCharaAIWorkPtr(obj) + 0xA0;
    void *target;

    _SCRGetCollisionTwoBoneRay(g, *(int *)(SkelFocusDef_PLAYER_SWORD + 0x8), *(int *)(SkelFocusDef_PLAYER_SWORDTOP + 0x8),
                               gcGlobalVar + 0x230, obj, func_0007BC80, 0);
    if (!(GetGeometryPointerCharColAttr(g) & 0x8))
        resetAttackPower();
    *(int *)(g + 0x40) = 1;
    target = GetGeometryPointerObject(g);
    SendCharaAttackMsg(obj, target, g, 0, (float)getSelectWeapon());
    *(int *)(g + 0x40) = 0;
}
