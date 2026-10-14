extern char *GetSCRCharaAIWorkPtr();

void SCRFuncHorseAdvertisFlag(int a, int b)
{
    *(int *)(GetSCRCharaAIWorkPtr(a) + 0x4204) = b;
}
