extern void *GetSCRCharaAIWorkPtr(void *);
extern void initInterestWork(int, char *);

void SCRFuncHorseInterestInit(void *actor)
{
    initInterestWork((int)actor, (char *)GetSCRCharaAIWorkPtr(actor) + 0x41B0);
}
