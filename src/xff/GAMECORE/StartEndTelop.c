extern int ScriptSpriteMenuObjDef_SPRITE_END_TELOP;
extern void _SCRStartSpriteMenuAnim(int, int, int, int *, int, float *);
extern void scrRun(void);

void StartEndTelop(float t)
{
    int done;
    float tt;
    tt = t;
    done = 0;
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_END_TELOP, 0, 0, &done, 0, &tt);
    while (done == 0)
        scrRun();
}
