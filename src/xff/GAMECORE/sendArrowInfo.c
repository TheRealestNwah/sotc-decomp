extern void *GetSCRCharaAIWorkPtr();

int sendArrowInfo(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x20));
}
