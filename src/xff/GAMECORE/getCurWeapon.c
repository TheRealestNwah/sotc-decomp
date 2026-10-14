extern void *GetSCRCharaAIWorkPtr();

int getCurWeapon(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x70));
}
