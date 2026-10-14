extern void *GetSCRCharaAIWorkPtr(void *);

int SCRGetBossPartsDamageNum(void *actor)
{
    return (*(int *)((char *)(*((void **)GetSCRCharaAIWorkPtr(actor))) + 0x54));
}
