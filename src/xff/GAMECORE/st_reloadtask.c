typedef int s128 __attribute__((mode(TI)));
struct Quad { s128 q; };
typedef struct {
    char pad0[0x88];
    long tcount;
    char pad90[0x280 - 0x90];
    char grp280[0x30];
    char grp2B0[0x30C - 0x2B0];
    int stage;
} GcGlobal;
extern GcGlobal gcGlobalVar;
extern int D_0017A2C0;
extern int D_0017A2C4;
extern int D_0017A2C8;
extern struct Quad B_001885D0;
extern struct Quad B_001885E0;
extern char SH_StageDataDEFAULT[];
extern char rootPtn[];
extern int DldSysUndefSymbol;

extern void scrRun(void);
extern int fadeChkStat(int);
extern void *SCRGetFirstObj(void *);
extern void YattsukeGetSeamlessAreaCenter(void *, int);
extern void ForceUnparentLayoutObj(void *);
extern void DebugSetObjectGeometry(void *, void *, void *);
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void reset_game_camera(void *);
extern void forceLoadSeamlessStage(void);
extern int SeamlessStageLoadComplete(void);
extern void iosStopPc(void);
extern void SetupStageManager(int);
extern void sheetMgrAllReqWait(int *);
extern void UnloadAllSeamlessStageObject(int);
extern void func_0001ABC0(void *);
extern void windowDeleteAllObjByGroup(int);
extern void seSopStageTypeAll(void);
extern void bgmStageInit(void);
extern void sheetMgrUnloadSegmentIndex(void *, int, int *);
extern void sheetMgrLoadSegmentIndex(void *, int, int *);
extern void st_WaitGPFinish(int);
extern char *gcGetStageData(int);
extern void func_0001BB48(void *, void *, void *, int);
extern int GetStageNumberNumber(void);
extern void setLightParamDefault(void);
extern void setFogParamDefault(void);
extern void fadeIn(int, float, int);
extern long iosGetTCountExtension(void);

static inline char *dldResolve(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((*h >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void st_reloadtask(void)
{
    int areaOk;
    struct Quad center;
    char *sheet;
    int r0, r1, r2;

    sheet = SH_StageDataDEFAULT;
    for (;;) {
        if (D_0017A2C4 == gcGlobalVar.stage && (areaOk = D_0017A2C8 >= 0)) {
            int area;
            void *obj;

            while (!fadeChkStat(2))
                scrRun();
            area = D_0017A2C8;
            obj = SCRGetFirstObj(gcGlobalVar.grp2B0);
            if (obj != 0) {
                YattsukeGetSeamlessAreaCenter(&center, area);
                __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                     "lqc2 vf6, 0x0(%1)\n"
                                     "vadd.xyz vf5, vf5, vf6\n"
                                     "sqc2 vf5, 0x0(%0)\n"
                                     : : "r"(&center), "r"(&B_001885D0) : "memory");
                ForceUnparentLayoutObj(obj);
                DebugSetObjectGeometry(obj, &B_001885E0, &center);
                reset_game_camera(get_game_camera(get_main_cameraman()));
            }
            scrRun();
            forceLoadSeamlessStage();
            while (!SeamlessStageLoadComplete())
                scrRun();
            D_0017A2C4 = -1;
        } else if (D_0017A2C4 != -1) {
            int id;
            char *p;
            int n;
            char *root;
            void *grp;

            iosStopPc();
            SetupStageManager(-1);
            sheetMgrAllReqWait(&r0);
            while ((unsigned)(r0 + 0xFFFF2151) >= 2)
                scrRun();
            UnloadAllSeamlessStageObject(3);
            func_0001ABC0(gcGlobalVar.grp280);
            windowDeleteAllObjByGroup(1);
            seSopStageTypeAll();
            bgmStageInit();
            if (gcGlobalVar.stage >= 0) {
                sheetMgrUnloadSegmentIndex(sheet, gcGlobalVar.stage, &r1);
                while ((unsigned)(r1 + 0xFFFF2151) >= 2)
                    scrRun();
            }
            st_WaitGPFinish(3);
            sheetMgrLoadSegmentIndex(sheet, D_0017A2C4, &r2);
            while ((unsigned)(r2 + 0xFFFF2151) >= 2)
                scrRun();
            root = rootPtn;
            {
                GcGlobal *g = &gcGlobalVar;

                grp = g->grp280;
            }
            SetupStageManager(D_0017A2C4);
            id = D_0017A2C4;
            gcGlobalVar.stage = id;
            p = dldResolve((unsigned int *)(gcGetStageData(id) + 4));
            if (p != 0)
                func_0001BB48(p, root, grp, 4);
            n = GetStageNumberNumber();
            gcGetStageData(n == -1 ? id : n);
            setLightParamDefault();
            setFogParamDefault();
            forceLoadSeamlessStage();
            if (D_0017A2C4 != 1)
                fadeIn(1, 1.0f, 1);
            D_0017A2C4 = -1;
            D_0017A2C0 = 0;
        }
        gcGlobalVar.tcount = iosGetTCountExtension();
        scrRun();
    }
}
