extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncSnakeCUpGroundInit(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x5A90)) = 1;
}
