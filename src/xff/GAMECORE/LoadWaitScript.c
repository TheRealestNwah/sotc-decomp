extern int D_0017B3F4;
extern int D_0017B3F8;
extern int D_0017B3FC;
extern int ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int *, int *);
extern void scrRun(void);

void LoadWaitScript(void)
{
    D_0017B3F4 = 1;
    D_0017B3F8 = 0;
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT, 0, 0, &D_0017B3F8, &D_0017B3F4, &D_0017B3FC);
    while (D_0017B3F8 == 0)
        scrRun();
}
