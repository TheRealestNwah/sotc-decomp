extern char gcGlobalVar[];
extern int rootPtn[];
extern void *SCRGetFirstObj(void *);
extern void nico_ResetPlayerHorseRidingControl(void *);
extern void st_unload_horse_char(void);
extern int createScriptObj(void (*)(void), int, int *, int, int, int, int, int);

static int func_00031728(void)
{
    nico_ResetPlayerHorseRidingControl(SCRGetFirstObj(gcGlobalVar + 0x2B4));
    return createScriptObj(st_unload_horse_char, 0, rootPtn, 0x1000, 0, 1, 0, 1);
}
