extern char gcGlobalVar[];
extern char RO_0017C910[];
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);

extern int rootPtn;
extern void st_playObjAnim();
extern void setScriptAnimationObjChildStatus();
extern void st_defaultAI();
extern void st_gameflow();
extern void st_controltarget();
extern void st_camfinalizer();
extern void nico_soundScriptStart();
extern void st_reloadtask();
extern void func_0000A990(int);
extern void func_0000B130();
extern void D_0000B560();
extern void func_0000B298();
extern void D_0000B2E0();
extern void func_0000B4E0();
extern void D_0000B530();
extern void D_0000B438();
extern void SetScriptAnimationGlobalBaseInfo(void *);
extern void SetScriptCharDefaultScriptFunc(void *);
extern void createBinaryMemoryInfoWindow(void);
extern void initSortDisplayObj(void);
extern void initdefaultaitask(void);
extern void CreateStageManager(int);
extern void CreateStageBoundaryManager(int);
extern void CreateBgmThread(void *);
extern void scrDemoInit(void);
extern void setBossPathColiGroup(void *);
extern void setHorsePathColiGroup(void *);

static void func_0000ACF8(void)
{
    void *info[11] = {
        gcGlobalVar + 0x228, gcGlobalVar + 0x280, gcGlobalVar + 0x284, gcGlobalVar + 0x278,
        gcGlobalVar + 0x27C, gcGlobalVar + 0x270, st_playObjAnim, (void *)4,
        gcGlobalVar + 0x2AC, setScriptAnimationObjChildStatus, gcGlobalVar + 0x288,
    };

    SetScriptAnimationGlobalBaseInfo(info);
    SetScriptCharDefaultScriptFunc(st_defaultAI);
    createBinaryMemoryInfoWindow();
    initSortDisplayObj();
    gcCreateScriptObj(func_0000B130, 0, &rootPtn, 0x1000, 0, 9, "st_disp");
    gcCreateScriptObj(st_gameflow, 0, &rootPtn, 0x2000, 0, 1, "st_gameflow");
    gcCreateScriptObj(st_controltarget, 0, &rootPtn, 0x4000, 0, 2, "st_controltarget");
    func_0000A990(7);
    gcCreateScriptObj(D_0000B560, 0, &rootPtn, 0x2000, 0, 8, "st_fogcolman");
    initdefaultaitask();
    gcCreateScriptObj(st_camfinalizer, 0, &rootPtn, 0x1000, 0, 7, "st_camfinalizer");
    gcCreateScriptObj(func_0000B298, 0, &rootPtn, 0x1000, 0, 2, "wind_task");
    gcCreateScriptObj(D_0000B2E0, 0, &rootPtn, 0x2800, 0, 8, "particle_task");
    CreateStageManager(2);
    CreateStageBoundaryManager(8);
    gcCreateScriptObj(func_0000B4E0, 0, &rootPtn, 0x1000, 0, 3, "beforeobjgeo");
    gcCreateScriptObj(D_0000B530, 0, &rootPtn, 0x1000, 0, 5, "afterobjgeo");
    gcCreateScriptObj(nico_soundScriptStart, 0, &rootPtn, 0x2000, 0, 4, "soundscript");
    CreateBgmThread(&rootPtn);
    gcCreateScriptObj(D_0000B438, 0, &rootPtn, 0x1000, 0, 1, "common_task");
    scrDemoInit();
    setBossPathColiGroup(gcGlobalVar + 0x244);
    setHorsePathColiGroup(gcGlobalVar + 0x244 + 0x18);
    gcCreateScriptObj(st_reloadtask, 0, &rootPtn, 0x2000, 0, 1, "st_reloadtask");
}

void *initgcchartest(void)
{
    return gcCreateScriptObj(func_0000ACF8, 0, *(void **)(gcGlobalVar + 0x308), 0x10000, 0, 1, RO_0017C910);
}
