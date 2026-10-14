struct TimeAttackEndView {
    char pad00[0xC];
    int flags;
    char pad10[8];
    float elapsed;
};

extern struct TimeAttackEndView g_TimeAttack;

float timeAttackTimeScriptEnd(void)
{
    g_TimeAttack.flags |= 0x20;
    return g_TimeAttack.elapsed;
}
