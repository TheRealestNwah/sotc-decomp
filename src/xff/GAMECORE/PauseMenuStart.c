extern void _SCRStartSpriteMenuAnim(void *def, int a, int b, int c, int d, int e);

extern void *ScriptSpriteMenuObjDef_SPRITE_PAUSE;

void PauseMenuStart(int a, int b)
{
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_PAUSE, 0, 0, a, 0, b);
}
