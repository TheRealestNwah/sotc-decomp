extern int isysGetThisSubThread();
extern int scrRunM();

int nico_commonBossAI_home(void)
{
    isysGetThisSubThread();
    return scrRunM(1);
}
