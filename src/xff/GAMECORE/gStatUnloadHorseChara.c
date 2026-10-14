extern void stagemanager_unloadstagecore(int);
extern int D_0017A294;

void gStatUnloadHorseChara(void)
{
    if (D_0017A294 != 0) {
        stagemanager_unloadstagecore(D_0017A294);
    }
    D_0017A294 = 0;
}
