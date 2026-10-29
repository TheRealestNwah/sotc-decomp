extern int D_0017AD3C;
extern void gameflowSetPauseEnable(int);
extern void isysRequestDeleteObj(int);

void nico_delOmakeItem(void)
{
    gameflowSetPauseEnable(1);
    isysRequestDeleteObj(D_0017AD3C);
}
