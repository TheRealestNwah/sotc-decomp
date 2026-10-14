extern void *GetSCRCharaAIWorkPtr(void *);

void *getWormIKWork(void *actor)
{
    return (void *)(((int)GetSCRCharaAIWorkPtr(actor) + 0x41B3) & ~0xF);
}
