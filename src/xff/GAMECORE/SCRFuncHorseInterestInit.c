extern int GetSCRCharaAIWorkPtr();
extern int initInterestWork();

int SCRFuncHorseInterestInit(int a)
{
    return initInterestWork(a, GetSCRCharaAIWorkPtr(a) + 16816);
}
