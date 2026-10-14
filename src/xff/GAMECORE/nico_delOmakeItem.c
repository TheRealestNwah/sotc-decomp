extern int D_0017AD3C;
extern void gameflowSetPauseEnable();
extern int isysRequestDeleteObj();

int nico_delOmakeItem(void)
{
    gameflowSetPauseEnable(1);
    return isysRequestDeleteObj(D_0017AD3C);
}
