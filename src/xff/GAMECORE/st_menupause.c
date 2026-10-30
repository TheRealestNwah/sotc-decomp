extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern int B_00184870;
extern int gstatTimeAttackMode;
extern int vschedGameTimeExec;
extern int gameflowStartMenuKaisou;
extern int D_0017A08C;
extern int SeList_pause;
extern void PauseGame(int);
extern void execPause(void);
extern void timeAttackPauseScriptBegin(void);
extern void fadeOut(float, int, int);
extern void setLayerFade(int);
extern void ReplayPauseScriptBegin(void);
extern void adpcmGamePause(int);
extern void sndSepPauseAll(int);
extern int sePlaySystemSound(int);
extern void scrRunM(int);

void st_menupause(void)
{
    scrInit(isysGetThisSubThread());
    if (B_00184870 != 0)
        return;
    if (gstatTimeAttackMode == 0) {
        PauseGame(1);
        vschedGameTimeExec = 0;
        execPause();
    } else {
        PauseGame(1);
        vschedGameTimeExec = 0;
        D_0017A08C = 2;
        if (gameflowStartMenuKaisou == 0) {
            timeAttackPauseScriptBegin();
        } else {
            fadeOut(0.4f, 1, 0);
            setLayerFade(0x19);
            ReplayPauseScriptBegin();
        }
    }
    adpcmGamePause(1);
    sndSepPauseAll(1);
    sePlaySystemSound(SeList_pause);
    scrRunM(0x32);
}
