extern void **GetSCRCharaAIWorkPtr();

void setBossAbsoluteDeath(void)
{
    (*(int *)((char *)(*GetSCRCharaAIWorkPtr()) + 0x48)) = 1;
}
