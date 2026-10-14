extern void *GetSCRCharaAIWorkPtr(void *);

int nico_returnPlayerRidingFlag(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0xD98));
}
