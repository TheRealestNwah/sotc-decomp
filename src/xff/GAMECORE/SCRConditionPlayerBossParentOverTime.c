extern char *getPlayerColCont2(int);
extern char *getSCRDataCtrlWork(void);

int SCRConditionPlayerBossParentOverTime(float time)
{
    return time <= *(float *)(getPlayerColCont2(*(int *)(getSCRDataCtrlWork() + 0x4078)) + 0x24);
}
