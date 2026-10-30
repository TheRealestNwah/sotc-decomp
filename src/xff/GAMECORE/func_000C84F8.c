typedef struct {
    int unk0;
    int state;
    int unk8;
    int flags;
} ModeState;
extern ModeState g_TimeAttack;
extern int D_0017B23C;
extern int ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_END;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

static void func_000C84F8(void)
{
    int *pending = &D_0017B23C;

    g_TimeAttack.state = 4;
    g_TimeAttack.flags &= ~0x10;
    if (*pending != 0) {
        *pending = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_TIME_ATTACK_END, 0, 0, pending, 0, 0);
    }
}
