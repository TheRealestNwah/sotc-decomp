extern void *isysGetThisSubThread(void);
extern void scrRunM(int);

void nico_commonBossAI_home(void)
{
    isysGetThisSubThread();
    scrRunM(1);
}
