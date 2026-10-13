extern void *GetSCRCharaAIWorkPtr();
extern float RO_0017D12C;

void SCRFuncBuddhaMissileInit(void)
{
    (*(float *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41B4)) = (float) RO_0017D12C;
}
