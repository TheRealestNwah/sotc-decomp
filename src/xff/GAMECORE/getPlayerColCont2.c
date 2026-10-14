extern void *GetSCRCharaAIWorkPtr(void *);

void *getPlayerColCont2(void *actor)
{
    return (char *)GetSCRCharaAIWorkPtr(actor) + 0xDD0;
}
