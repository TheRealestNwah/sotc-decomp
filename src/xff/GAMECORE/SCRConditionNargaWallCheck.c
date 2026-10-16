extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionNargaWallCheck(void *actor, int wall)
{
    return wall == *(int *)((char *)GetSCRCharaAIWorkPtr(actor) + 0x5AA0);
}
