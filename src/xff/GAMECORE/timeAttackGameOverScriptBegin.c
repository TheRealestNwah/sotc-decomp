typedef struct { int a; int b; int c; unsigned int flags; float t; int d; int e; } TimeAttack;
extern TimeAttack g_TimeAttack;
extern int D_0017B240;
extern int D_0017B244;
extern int ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_OVER_BG;
extern int ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_OVER_ALERT;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

void timeAttackGameOverScriptBegin(void)
{
    g_TimeAttack.c = 1;
    g_TimeAttack.flags &= ~0x80;
    g_TimeAttack.b = 7;
    if (D_0017B240 != 0) {
        D_0017B240 = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_OVER_BG, 0, 0, &D_0017B240, 0, 0);
    }
    g_TimeAttack.c = 1;
    g_TimeAttack.b = 7;
    g_TimeAttack.flags &= ~0x40;
    if (D_0017B244 != 0) {
        D_0017B244 = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_OVER_ALERT, 0, 0, &D_0017B244, 0, 0);
    }
}
