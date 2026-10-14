struct TimeAttackView {
    char pad00[0x14];
    volatile float limit;
    volatile float elapsed;
};

extern struct TimeAttackView g_TimeAttack;

float GetTimeAttackTimeLimit(void)
{
    float elapsed = g_TimeAttack.elapsed;
    float limit = g_TimeAttack.limit;
    return limit - elapsed;
}
