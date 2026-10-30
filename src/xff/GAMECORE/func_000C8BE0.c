typedef struct {
    int unk0;
    int state;
    int unk8;
    int flags;
} ModeState;
extern ModeState g_Replay;
extern int D_0017B264;
extern int ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_END;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

static void func_000C8BE0(void)
{
    int *pending = &D_0017B264;

    g_Replay.state = 4;
    g_Replay.flags &= ~0x10;
    if (*pending != 0) {
        *pending = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_END, 0, 0, pending, 0, 0);
    }
}
