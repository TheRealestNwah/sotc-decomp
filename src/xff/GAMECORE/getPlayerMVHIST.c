extern void *GetSCRCharaAIWorkPtr(void *);

void *getPlayerMVHIST(void *actor)
{
    return (char *)GetSCRCharaAIWorkPtr(actor) + 0xE00;
}
