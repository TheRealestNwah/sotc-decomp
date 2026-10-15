extern void _SCRStartSpriteMenuAnim(void *def, int a, int b, int c, int d, int e);

extern void *ScriptSpriteMenuObjDef_SPRITE_OPTION;

void OptionMenuStart(int a, int b)
{
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_OPTION, 0, 0, a, 0, b);
}
