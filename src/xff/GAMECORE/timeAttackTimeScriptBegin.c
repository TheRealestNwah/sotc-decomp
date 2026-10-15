typedef struct { int a; int b; int c; unsigned int flags; int d; float t; int e; } TimeAttack;
extern TimeAttack g_TimeAttack;
extern int D_0017B248;
extern int ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_TIME;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

void timeAttackTimeScriptBegin(float t)
{
    g_TimeAttack.t = t;
    g_TimeAttack.flags &= ~0x20;
    g_TimeAttack.e = 0;
    g_TimeAttack.d = 0;
    if (D_0017B248 != 0) {
        D_0017B248 = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_TIME, 0, 0, &D_0017B248, 0, 0);
    }
}
