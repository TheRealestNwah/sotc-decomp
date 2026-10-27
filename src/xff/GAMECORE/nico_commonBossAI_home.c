extern void *isysGetThisSubThread(void);
extern int scrRunM();

int nico_commonBossAI_home(void)
{
    isysGetThisSubThread();
    return scrRunM(1);
}
