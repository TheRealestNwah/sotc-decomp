extern float getBossWeakCurDamage(void *, long);

int SCRConditionMyselfWeakDamaged(void *actor, int a1, int a2, int a3, int t0, long key)
{
    return getBossWeakCurDamage(actor, key) != 0.0f;
}
