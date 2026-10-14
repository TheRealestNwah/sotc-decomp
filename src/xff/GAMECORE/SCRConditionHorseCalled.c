extern void *getSCRDataCtrlWork(void *);
extern int IsHorseCalled_withFlgOff(void *);

int SCRConditionHorseCalled(void *actor)
{
    return IsHorseCalled_withFlgOff(*(void **)(((char *)getSCRDataCtrlWork(actor)) + 0x4078));
}
