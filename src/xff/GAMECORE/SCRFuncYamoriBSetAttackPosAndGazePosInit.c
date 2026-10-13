extern void *GetSCRCharaAIWorkPtr();

void SCRFuncYamoriBSetAttackPosAndGazePosInit(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41C0)) = 0;
}
