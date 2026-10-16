extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern void SaveLayoutObjGroupAllGeo(void);
extern char *GetLayoutClass(void *);
extern void backStageGobjSaveWithPos(void *, void *, void *);
extern void func_00018E00(int, int);

void gStatChekcPointSaveHookPlayerHorsePos(void *ppos, void *pdir, void *hpos, void *hdir, int arg)
{
    void *player = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    void *horse = SCRGetFirstObj(gcGlobalVar + 0x2B4);

    SaveLayoutObjGroupAllGeo();
    backStageGobjSaveWithPos(*(void **)(GetLayoutClass(player) + 0x1A4), ppos, pdir);
    if (horse != 0 && hpos != 0)
        backStageGobjSaveWithPos(*(void **)(GetLayoutClass(horse) + 0x1A4), hpos, hdir);
    func_00018E00(arg, horse != 0);
}
