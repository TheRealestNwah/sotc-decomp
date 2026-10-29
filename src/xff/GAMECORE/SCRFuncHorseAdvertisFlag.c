extern void *GetSCRCharaAIWorkPtr(void *);
void SCRFuncHorseAdvertisFlag(void *actor, int flag)
{
    *(int *)((char *)GetSCRCharaAIWorkPtr(actor) + 0x4204) = flag;
}
