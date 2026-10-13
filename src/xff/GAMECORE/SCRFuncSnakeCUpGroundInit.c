extern void *GetSCRCharaAIWorkPtr();

void SCRFuncSnakeCUpGroundInit(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x5A90)) = 1;
}
