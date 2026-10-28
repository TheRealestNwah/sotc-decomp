extern int gstatTimeAttackMode;
extern void SetTimeAttackTimeFlag(int);

void gStatStopTimeAttack(void)
{
    gstatTimeAttackMode = 3;
    SetTimeAttackTimeFlag(0);
}
