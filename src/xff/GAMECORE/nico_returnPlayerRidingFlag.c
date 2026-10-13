extern void *GetSCRCharaAIWorkPtr();

int nico_returnPlayerRidingFlag(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0xD98));
}
