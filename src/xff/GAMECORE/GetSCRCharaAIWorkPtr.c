extern void *GetScriptCharacterClass();

int GetSCRCharaAIWorkPtr(void)
{
    return (*(int *)((char *)(GetScriptCharacterClass()) + 0x1200));
}
