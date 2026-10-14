typedef struct { char pad[0xC]; int flags; } TimeAttack;
extern TimeAttack g_TimeAttack;
void CloseTimeAttackMenu(int a)
{
    if (a == 1)
        g_TimeAttack.flags |= 0xFE;
    else
        g_TimeAttack.flags |= a;
}
