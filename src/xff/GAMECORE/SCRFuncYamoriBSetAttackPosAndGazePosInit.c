extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncYamoriBSetAttackPosAndGazePosInit(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41C0)) = 0;
}
