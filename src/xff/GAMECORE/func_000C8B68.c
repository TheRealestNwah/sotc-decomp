typedef struct {
    int unk0;
    int state;
    int unk8;
    int flags;
} ModeState;
extern ModeState g_Replay;
extern int D_0017B260;
extern int ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_RETRY;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

static void func_000C8B68(void)
{
    int *pending = &D_0017B260;

    g_Replay.state = 3;
    g_Replay.flags &= ~8;
    if (*pending != 0) {
        *pending = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_RETRY, 0, 0, pending, 0, 0);
    }
}
