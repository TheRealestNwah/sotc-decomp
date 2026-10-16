extern int D_0017AC40;
extern int B_0018B6A0;
extern char RO_0017DE68[];
extern char rootPtn[];
extern int ScriptSpriteMenuObjDef_SPRITE_LOAD;
extern void LoadWaitScript(void);
extern void gcCreateScriptObj(void (*)(void), int, void *, int, int, int, char *);
extern void _SCRStartSpriteMenuAnim(int, int, int, int, int, int);

void bootMemoryCardLoadScriptNoBlock(int a, int b)
{
    if (D_0017AC40 != 0)
        return;
    gcCreateScriptObj(LoadWaitScript, 0, rootPtn, 0x1000, 0, 1, RO_0017DE68);
    B_0018B6A0 = b;
    D_0017AC40 = 2;
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_LOAD, 0, a, 0, 0, 0);
    D_0017AC40 = 0;
}
