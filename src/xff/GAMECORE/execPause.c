extern int ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT;
extern char D_0017B3F0[];
extern int _SCRStartSpriteMenuAnim(int, int, int, void *, int, int);
int execPause(void)
{
    return _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT, 0, 0, D_0017B3F0, 0, 0);
}
