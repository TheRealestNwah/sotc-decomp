extern unsigned char g_TimeAttack[1];

void SetTimeAttackTimeFlag(int arg0)
{
    (*(int *)((char *)(&g_TimeAttack) + 0x10)) = arg0;
}
