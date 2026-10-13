extern void *GetSCRCharaAIWorkPtr();

int getTorchObj(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x150));
}
