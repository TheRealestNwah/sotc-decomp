extern int D_0017AC40;
extern int ScriptSpriteMenuObjDef_SPRITE_SAVE;
extern void _SCRStartSpriteMenuAnim(int, int, int, int, int, void *);

void bootMemoryCardSaveScriptNoBlock(void *a)
{
    int *p = &D_0017AC40;
    if (*p == 0) {
        *p = 1;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_SAVE, 0, 0, 0, 0, a);
        *p = 0;
    }
}
