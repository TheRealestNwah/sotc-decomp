extern void *GetSCRCharaAIWorkPtr(void *);

void *getSCRDataCtrlWork(void *actor)
{
    return (void *)(((unsigned int)GetSCRCharaAIWorkPtr(actor) + 0x13) & ~0xF);
}
