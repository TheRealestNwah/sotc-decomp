typedef struct { int a; int b; int c; unsigned int flags; } Replay;
extern Replay g_Replay;
extern int D_0017B268;
extern int D_0017B26C;
extern int ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_OVER_BG;
extern int ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_OVER_ALERT;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);

void ReplayGameOverScriptBegin(void)
{
    g_Replay.c = 1;
    g_Replay.b = 7;
    g_Replay.flags &= ~0x80;
    if (D_0017B268 != 0) {
        D_0017B268 = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_OVER_BG, 0, 0, &D_0017B268, 0, 0);
    }
    g_Replay.c = 1;
    g_Replay.b = 7;
    g_Replay.flags &= ~0x40;
    if (D_0017B26C != 0) {
        D_0017B26C = 0;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_REPLAY_MODE_OVER_ALERT, 0, 0, &D_0017B26C, 0, 0);
    }
}
