extern int ScriptSpriteMenuObjDef_SPRITE_SCE_LOGO_LAYOUT;
extern void _SCRStartSpriteMenuAnim(int, int, int, int, int, int);

void bootscelogoscript(int a, int b)
{
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_SCE_LOGO_LAYOUT, 0, 0, a, b, 0);
}
