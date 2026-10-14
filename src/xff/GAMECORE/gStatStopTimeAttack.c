extern int gstatTimeAttackMode;
extern int SetTimeAttackTimeFlag();

int gStatStopTimeAttack(void)
{
    gstatTimeAttackMode = 3;
    return SetTimeAttackTimeFlag(0);
}
