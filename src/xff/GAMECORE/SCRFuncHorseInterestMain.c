extern char *GetSCRCharaAIWorkPtr(void *);
extern int updateInterestWork(void *, void *, int);

int SCRFuncHorseInterestMain(void *actor, int a, int b, int c, int d, int e)
{
    return updateInterestWork(actor, GetSCRCharaAIWorkPtr(actor) + 0x41B0, e);
}
