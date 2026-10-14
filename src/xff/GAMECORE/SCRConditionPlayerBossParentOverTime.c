extern void *getPlayerColCont2(void *);
extern char *getSCRDataCtrlWork(void);

int SCRConditionPlayerBossParentOverTime(float time)
{
    return time <= *(float *)((char *)getPlayerColCont2(*(void **)(getSCRDataCtrlWork() + 0x4078)) + 0x24);
}
