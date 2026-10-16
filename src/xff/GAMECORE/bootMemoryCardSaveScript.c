extern int D_0017AC40;
extern int ScriptSpriteMenuObjDef_SPRITE_SAVE;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, int);
extern void scrRun(void);

void bootMemoryCardSaveScript(int param)
{
    int done;

    if (D_0017AC40 != 0)
        return;
    D_0017AC40 = 1;
    done = 0;
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_SAVE, 0, 0, &done, 0, param);
    if (done == 0) {
        do {
            scrRun();
        } while (done == 0);
    }
    D_0017AC40 = 0;
}
