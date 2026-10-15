extern char *GetSCRCharaAIWorkPtr(void *);

void setHorseForceScriptKey(void *actor, int *key)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    if (key != 0)
        *(long *)(w + 0x4208) |= 1L << key[1];
}
