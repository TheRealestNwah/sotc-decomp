extern int D_0017A294;
extern char rootPtn[];
extern void stagemanager_restartstagecore(void *, int, int, int);

void gStatRestartHorseChara(void)
{
    int s = D_0017A294;
    if (s != 0)
        stagemanager_restartstagecore(rootPtn, s, -1, 0);
}
