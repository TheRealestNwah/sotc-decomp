extern float getBossWeakCurDamage(void *, int);

int SCRConditionMyselfWeakDamaged(void *actor, int a1, int a2, int a3, int t0, int index)
{
    return getBossWeakCurDamage(actor, index) != 0.0f;
}
