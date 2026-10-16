extern float getBossPartsCurDamage(void *, int);

int SCRConditionMyselfPartsDamaged(void *actor, int a1, int a2, int a3, int t0, int index)
{
    return getBossPartsCurDamage(actor, index) != 0.0f;
}
