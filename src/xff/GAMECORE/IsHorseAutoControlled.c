extern void *GetSCRCharaAIWorkPtr();

unsigned char IsHorseAutoControlled(void)
{
    return (*(unsigned char *)((char *)(GetSCRCharaAIWorkPtr()) + 0xD9D));
}
