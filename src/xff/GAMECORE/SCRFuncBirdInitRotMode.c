extern void *GetSCRCharaAIWorkPtr();

void SCRFuncBirdInitRotMode(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41D0)) = 1;
}
