extern unsigned char g_TimeAttack[];

float GetTimeAttackTimer(void)
{
    return (*(float *)((char *)(g_TimeAttack) + 0x18));
}
