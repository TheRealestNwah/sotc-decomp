typedef struct { int a; int b; int c; unsigned int flags; float t; int d; int e; } TimeAttack;
extern TimeAttack g_TimeAttack;
extern int D_0017B230;
extern int ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_IN;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

void timeAttackInScriptBegin(void)
{
    g_TimeAttack.c = 0;
    g_TimeAttack.b = 1;
    g_TimeAttack.flags &= ~2;
    if (D_0017B230 != 0) {
        D_0017B230 = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_IN, 0, 0, &D_0017B230, 0, 0);
    }
}
