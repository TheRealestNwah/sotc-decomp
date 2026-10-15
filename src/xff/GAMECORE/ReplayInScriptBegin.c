typedef struct { int a; int b; int c; unsigned int flags; } Replay;
extern Replay g_Replay;
extern int D_0017B258;
extern int ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_IN;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

void ReplayInScriptBegin(void)
{
    g_Replay.c = 0;
    g_Replay.b = 1;
    g_Replay.flags &= ~2;
    if (D_0017B258 != 0) {
        D_0017B258 = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_IN, 0, 0, &D_0017B258, 0, 0);
    }
}
