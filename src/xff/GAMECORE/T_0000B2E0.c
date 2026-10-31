typedef struct {
    char p0[0x50];
    long t50;
    long t58;
    char p60[0x110];
    float f170;
    char p174[0xC];
    float f180;
    char p184[0xAC];
    char v230[0x10];
    char v240[4];
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;
extern long iosGetTCountExtension(void);
extern void ptclmanFrameInit(void);
extern void *GAMEUTIL_get_player_obj(void);
extern int func_0000B5E0(void);
extern void doit_particle_manager(void *, void *, void *, int, float, float);
extern void disp_particle_manager(void);
extern void updateSpecialEffectManager(void);
extern void scrRun(void);

static void T_0000B2E0(void)
{
    void *player;

    for (;;) {
        ptclmanFrameInit();
        gcGlobalVar.t50 = iosGetTCountExtension();
        player = GAMEUTIL_get_player_obj();
        doit_particle_manager(gcGlobalVar.v230, gcGlobalVar.v240, player, func_0000B5E0(), gcGlobalVar.f180,
                              gcGlobalVar.f170);
        disp_particle_manager();
        gcGlobalVar.t58 = iosGetTCountExtension();
        updateSpecialEffectManager();
        scrRun();
    }
}
