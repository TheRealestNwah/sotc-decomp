typedef struct { int a; int b; int c; unsigned int flags; float t; int d; int e; } TimeAttack;
extern TimeAttack g_TimeAttack;
extern int D_0017B234;
extern int ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_PAUSE;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

void timeAttackPauseScriptBegin(void)
{
    g_TimeAttack.c = 0;
    g_TimeAttack.b = 2;
    g_TimeAttack.flags &= ~4;
    if (D_0017B234 != 0) {
        D_0017B234 = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_PAUSE, 0, 0, &D_0017B234, 0, 0);
    }
}
