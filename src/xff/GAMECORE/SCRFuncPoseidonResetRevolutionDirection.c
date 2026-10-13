extern void *GetSCRCharaAIWorkPtr();

void SCRFuncPoseidonResetRevolutionDirection(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41C8)) = 0;
}
