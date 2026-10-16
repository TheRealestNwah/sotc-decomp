extern int ScriptSpriteMenuObjDef_SPRITE_CHOOSE_LANGUAGE_LAYOUT;
extern void _SCRStartSpriteMenuAnim(int, int, int, int, int, int);

void bootChooseLangScript(void)
{
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_CHOOSE_LANGUAGE_LAYOUT, 0, 0, 0, 0, 0);
}
