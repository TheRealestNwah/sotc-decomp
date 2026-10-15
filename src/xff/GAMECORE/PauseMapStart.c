extern void _SCRStartSpriteMenuAnim(void *def, int a, int b, int c, int d, int e);

extern void *ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT;

void PauseMapStart(int a)
{
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT, 0, 0, a, 0, 0);
}
