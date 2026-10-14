extern void *GetSCRCharaAIWorkPtr(void *);

unsigned char IsHorseAutoControlled(void *actor)
{
    return (*(unsigned char *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0xD9D));
}
