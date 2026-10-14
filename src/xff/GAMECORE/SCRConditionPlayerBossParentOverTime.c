extern void *getPlayerColCont2(void *);
extern void *getSCRDataCtrlWork(void *);

int SCRConditionPlayerBossParentOverTime(void *actor, float time)
{
    return time <= *(float *)((char *)getPlayerColCont2(*(void **)(((char *)getSCRDataCtrlWork(actor)) + 0x4078)) + 0x24);
}
