extern unsigned char g_TimeAttack[1];

float GetTimeAttackTimer(void)
{
    return (*(float *)((char *)(&g_TimeAttack) + 0x18));
}
