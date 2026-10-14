extern void *GetSCRCharaAIWorkPtr(void *);
extern float RO_0017D12C;

void SCRFuncBuddhaMissileInit(void *actor)
{
    (*(float *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41B4)) = (float) RO_0017D12C;
}
