extern void *getSCRDataCtrlWork(void *);

int SCRConditionHintEqualPlayCount(void *actor, int count)
{
    return count == *(int *)((char *)getSCRDataCtrlWork(actor) + 0x40E8);
}
