typedef struct {
    int unk0;
    int state;
    int unk8;
    int flags;
} ModeState;
extern ModeState g_Replay;
extern int D_0017B26C;
extern int ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_OVER_ALERT;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

static void func_000C8C58(void)
{
    int *pending = &D_0017B26C;

    g_Replay.unk8 = 1;
    g_Replay.state = 7;
    g_Replay.flags &= ~0x40;
    if (*pending != 0) {
        *pending = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_OVER_ALERT, 0, 0, pending, 0, 0);
    }
}
