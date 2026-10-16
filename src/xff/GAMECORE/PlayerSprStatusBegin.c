extern int D_0017B06C;
extern int ScriptSpriteObjDef_SPRITE_WEAPON_SIGHT;
extern int ScriptSpriteObjDef_SPRITE_WEAPON;
extern int ScriptSpriteMenuObjDef_SPRITE_PLAYER_LIFE_LAYOUT;
extern void _SCRStartSpriteAnim(int, int, int, int, int *, int);
extern void _SCRStartSpriteMenuAnim(int, int, int, int, int *, int);

void PlayerSprStatusBegin(void)
{
    if (D_0017B06C != 0)
        return;
    D_0017B06C = 1;
    _SCRStartSpriteAnim(ScriptSpriteObjDef_SPRITE_WEAPON_SIGHT, 0, 0, 0, &D_0017B06C, 0);
    _SCRStartSpriteAnim(ScriptSpriteObjDef_SPRITE_WEAPON, 0, 0, 0, &D_0017B06C, 0);
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_PLAYER_LIFE_LAYOUT, 0, 0, 0, &D_0017B06C, 0);
}
