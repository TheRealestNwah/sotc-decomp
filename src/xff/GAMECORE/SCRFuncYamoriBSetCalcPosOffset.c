extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncYamoriBSetCalcPosOffset(void *actor, float fparg0)
{
    (*(float *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41C4)) = fparg0;
}
