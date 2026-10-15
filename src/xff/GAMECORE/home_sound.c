extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern int SeList_st03_air_0;
extern int SeList_st03_wind1_0;
extern int sePlayStageEnv(int, int, int);

void home_sound(void)
{
    scrInit(isysGetThisSubThread());
    sePlayStageEnv(SeList_st03_air_0, 0, 0);
    sePlayStageEnv(SeList_st03_wind1_0, 0, 0);
}
