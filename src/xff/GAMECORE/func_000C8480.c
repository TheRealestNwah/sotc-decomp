typedef struct {
    int unk0;
    int state;
    int unk8;
    int flags;
} TimeAttack;
extern TimeAttack g_TimeAttack;
extern int D_0017B238;
extern int ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_RETRY;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

static void func_000C8480(void)
{
    int *retry = &D_0017B238;

    g_TimeAttack.state = 3;
    g_TimeAttack.flags &= ~8;
    if (*retry != 0) {
        *retry = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_RETRY, 0, 0, retry, 0, 0);
    }
}
