extern void *GetSCRCharaAIWorkPtr(void *);

int getCurWeapon(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x70));
}
