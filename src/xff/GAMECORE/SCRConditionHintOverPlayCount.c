extern void *getSCRDataCtrlWork(void *);

int SCRConditionHintOverPlayCount(void *actor, int count)
{
    return *(int *)((char *)getSCRDataCtrlWork(actor) + 0x40E8) >= count;
}
