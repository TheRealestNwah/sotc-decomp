extern int D_0017B070;
extern void *ScriptSpriteMenuObjDef_SPRITE_BOSS_LIFE_LAYOUT;
extern void _SCRStartSpriteMenuAnim(void *, int, int, int, int *, int);

void BossSprStatusBegin(void)
{
    if (D_0017B070 == 0) {
        D_0017B070 = 1;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_BOSS_LIFE_LAYOUT, 0, 0, 0, &D_0017B070, 0);
    }
}
