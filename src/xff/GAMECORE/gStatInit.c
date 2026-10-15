extern int D_0017A298, D_0017A2A0;
extern char B_00188550[];
extern void omakeStatInit(int, void *, int);
extern void gameFlagInit(void);
extern void bossStatInit(void);
extern void backStageInit(void);
extern void time_attack_init_gstat_adrs(void);
extern void func_00018E00(int, int);

void gStatInit(void)
{
    omakeStatInit(D_0017A2A0, D_0017A298 != 0 ? B_00188550 : 0, 0);
    gameFlagInit();
    bossStatInit();
    backStageInit();
    time_attack_init_gstat_adrs();
    func_00018E00(0, 1);
}
