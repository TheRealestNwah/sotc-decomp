extern void *GetSCRCharaAIWorkPtr();

void SCRFuncYamoriBSetCalcPosOffset(float fparg0)
{
    (*(float *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41C4)) = fparg0;
}
