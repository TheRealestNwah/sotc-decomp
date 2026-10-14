extern int gstatTimeAttackMode;
extern int SetTimeAttackTimeFlag();

int gStatStartTimeAttack(void)
{
    gstatTimeAttackMode = 2;
    return SetTimeAttackTimeFlag(1);
}
