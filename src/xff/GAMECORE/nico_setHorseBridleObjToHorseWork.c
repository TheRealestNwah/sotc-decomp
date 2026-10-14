extern char *GetSCRCharaAIWorkPtr();

void nico_setHorseBridleObjToHorseWork(int a, int b)
{
    *(int *)(GetSCRCharaAIWorkPtr(a) + 0x4248) = b;
}
