typedef struct {
    int pad0;
    int state;
    int active;
    unsigned int flags;
} TimeAttack;

extern TimeAttack g_TimeAttack;
extern int D_0017B244;
extern int ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_OVER_ALERT;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

static void func_000C8570(void)
{
    g_TimeAttack.active = 1;
    g_TimeAttack.state = 7;
    g_TimeAttack.flags &= ~0x40;
    if (D_0017B244) {
        D_0017B244 = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_OVER_ALERT, 0, 0, &D_0017B244, 0, 0);
    }
}
