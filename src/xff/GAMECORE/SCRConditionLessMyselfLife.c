extern void *SCRGetBossWork(void *);

int SCRConditionLessMyselfLife(void *actor, float fparg0)
{
    int var_v1;
    void *temp_v0;

    temp_v0 = SCRGetBossWork(actor);
    var_v1 = 1;
    if (!((((*(float *)((char *)(temp_v0) + 0x44)) / (*(float *)((char *)(temp_v0) + 0x40))) * 100.0f) <= fparg0)) {
        var_v1 = 0;
    }
    return var_v1;
}
