extern void *GetSCRCharaAIWorkPtr(void *);

void setBossAbsoluteDeath(void *actor)
{
    (*(int *)((char *)(*((void **)GetSCRCharaAIWorkPtr(actor))) + 0x48)) = 1;
}
