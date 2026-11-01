extern char *GetSCRCharaAIWorkPtr(void);
extern char *SkelFocusDef_PLAYER_SWORD;
extern char *SkelFocusDef_PLAYER_SWORDTOP;
extern char gcGlobalVar[];
extern void func_0007BC80(void);
extern void _SCRGetCollisionTwoBoneRay(void *, int, int, void *, void *, void (*)(void), int);
extern int GetGeometryPointerCharColAttr(void *);
extern void resetAttackPower(void);
extern void *GetGeometryPointerObject(void *);
extern int getSelectWeapon(void);
extern void SendCharaAttackMsg(void *, void *, void *, int, float);

static void T_00079BD8(void *p)
{
    char *w = GetSCRCharaAIWorkPtr() + 0xA0;
    void *g;

    _SCRGetCollisionTwoBoneRay(w, *(int *)(SkelFocusDef_PLAYER_SWORD + 8), *(int *)(SkelFocusDef_PLAYER_SWORDTOP + 8), gcGlobalVar + 0x230, p, func_0007BC80, 0);
    if (!(GetGeometryPointerCharColAttr(w) & 8)) {
        resetAttackPower();
    }
    *(int *)(w + 0x40) = 1;
    g = GetGeometryPointerObject(w);
    SendCharaAttackMsg(p, g, w, 0, (float)getSelectWeapon());
    *(int *)(w + 0x40) = 0;
}
