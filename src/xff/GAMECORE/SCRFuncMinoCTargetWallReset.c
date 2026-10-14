extern void *GetSCRCharaAIWorkPtr();

void SCRFuncMinoCTargetWallReset(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41F8)) = 0;
}
