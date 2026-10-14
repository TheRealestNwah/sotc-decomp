extern int gameflowGetJumpSekiban();
extern void gameflowSetJumpSekiban(int);

int SCRConditionHorseForceStandby(void)
{
    int r = gameflowGetJumpSekiban();

    gameflowSetJumpSekiban(0);
    return r;
}
