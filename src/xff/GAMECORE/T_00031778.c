extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern void gameflowSetPos(void *, float, float, float, float, float, float);

static void T_00031778(void)
{
    gameflowSetPos(SCRGetFirstObj(gcGlobalVar + 0x2B0), 348.0f, -59.0f, -2047.0f, 0.0f, 0.0f, 0.0f);
}
