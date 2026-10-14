extern void gameFlagInit(void);
extern void bossStatInit(void);
extern void backStageInit(void);
extern void time_attack_init_gstat_adrs(void);
extern void func_00018E00(int, int);

void gStatInitNotOmakeInit(void)
{
    gameFlagInit();
    bossStatInit();
    backStageInit();
    time_attack_init_gstat_adrs();
    func_00018E00(0, 1);
}
