extern int ScriptSpriteMenuObjDef_SPRITE_BOOT_PROGRESSIVE_ALERT;
extern void _SCRStartSpriteMenuAnim(int, int, int, int, int, int);

void bootprogressivecheck(int a)
{
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_BOOT_PROGRESSIVE_ALERT, 0, 0, a, 0, 0);
}
