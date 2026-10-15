extern char *getSCRDataCtrlWork(void *);

int SCRConditionTargetAttrOfInside(void *actor, int a, int b, int c, long mask, long value)
{
    return value == (*(long *)(getSCRDataCtrlWork(actor) + 0x4190) & mask);
}
