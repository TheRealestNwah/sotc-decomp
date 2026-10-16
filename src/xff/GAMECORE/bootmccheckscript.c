extern int ScriptSpriteMenuObjDef_SPRITE_BOOT_ALERT_LAYOUT;
extern void _SCRStartSpriteMenuAnim(int, int, int, int, int, int);

void bootmccheckscript(int a, int b)
{
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_BOOT_ALERT_LAYOUT, 0, 0, a, 0, b);
}
