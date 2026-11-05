typedef struct {
    char pad000[0x170];
    float x170;
    char pad174[0x188 - 0x174];
    float x188;
    char pad18C[4];
    float x190;
    char pad194[0x270 - 0x194];
    char group[0x314 - 0x270];
    char x314[1];
} GlobalVar;

typedef struct {
    char pad000[0x370];
    short x370;
    char pad372[0x94C - 0x372];
    int x94C;
} Chara;

typedef struct {
    char pad0000[0x1204];
    int x1204;
} ScriptChara;

extern GlobalVar gcGlobalVar;
extern int __gameMode;
extern int D_0017A920;
extern int D_0017A924;
extern int get_main_cameraman(void);
extern int get_main_cameraman_camera_obj(void);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern int GetLayoutClass(int);
extern Chara *GetCharacterClass(int);
extern int get_cur_camera_target(int);
extern void DebugControl(int, int, void *, float, float, float, int);
extern void CharaCtrlAIControl(int, int, float, float);
extern ScriptChara *GetScriptCharacterClass(int);
extern void CharaCtrlPlayableControlExt(int, int, void *, float);
extern void scrRun(void);

void st_controltarget(void)
{
    int cm;
    int camobj;
    int *g;
    int o;
    Chara *c;
    int dbg;

    for (;;) {
        cm = get_main_cameraman();
        if (cm != 0) {
            o = 0;
            camobj = get_main_cameraman_camera_obj();
            for (g = isysGroupForFirst(gcGlobalVar.group, 0); g != 0; g = isysGroupForNext(g, 0)) {
                o = *g;
                __asm__ __volatile__("pref 0, 0(%0)" : : "r"(o));
                if (GetLayoutClass(o) == 0)
                    continue;
                dbg = 0;
                c = GetCharacterClass(o);
                if (c != 0)
                    c->x94C = 0;
                if (o == get_cur_camera_target(cm) && !(__gameMode & 1)) {
                    dbg = 1;
                    if (c != 0)
                        c->x94C = 1;
                }
                if (dbg != 0) {
                    DebugControl(o, camobj, gcGlobalVar.x314,
                                 gcGlobalVar.x170, gcGlobalVar.x188, gcGlobalVar.x190, D_0017A924);
                } else if (c != 0) {
                    if (c->x370 == 4) {
                        if (D_0017A920 != 0) {
                        GetScriptCharacterClass(o)->x1204 = 1;
                        CharaCtrlPlayableControlExt(o, camobj, gcGlobalVar.x314, gcGlobalVar.x190);
                    } else {
                        GetScriptCharacterClass(o)->x1204 = 0;
                        CharaCtrlAIControl(o, camobj, gcGlobalVar.x188, gcGlobalVar.x190);
                        }
                    } else {
                        CharaCtrlAIControl(o, camobj, gcGlobalVar.x188, gcGlobalVar.x190);
                    }
                }
            }
            if (o != 0)
                isysGroupForExit(o, 0);
        }
        scrRun();
    }
}
