extern void *GetSCRCharaAIWorkPtr(void *);

void *getPlayerColCont(void *actor)
{
    return (char *)GetSCRCharaAIWorkPtr(actor) + 0xDC0;
}
