extern int gstatTimeAttackMode;
extern void SetTimeAttackTimeFlag(int);

void gStatStartTimeAttack(void)
{
    gstatTimeAttackMode = 2;
    SetTimeAttackTimeFlag(1);
}
