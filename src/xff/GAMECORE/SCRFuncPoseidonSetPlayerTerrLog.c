extern char *GetSCRCharaAIWorkPtr(void *);
void SCRFuncPoseidonSetPlayerTerrLog(void *actor, int value)
{
    char *w=GetSCRCharaAIWorkPtr(actor);
    if ((unsigned int)(value - 1) < 2U) *(int *)(w + 0x41CC) = value;
}
