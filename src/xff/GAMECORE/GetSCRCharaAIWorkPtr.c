extern void *GetScriptCharacterClass(void *);

void *GetSCRCharaAIWorkPtr(void *actor)
{
    void *script;

    script = GetScriptCharacterClass(actor);
    return *(void **)((char *)script + 0x1200);
}
