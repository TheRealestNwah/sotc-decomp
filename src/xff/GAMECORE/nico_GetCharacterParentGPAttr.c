extern char *GetCharacterClass(void *);

long nico_GetCharacterParentGPAttr(void *actor, long mask)
{
    char *c = GetCharacterClass(actor);
    if (*(int *)(c + 0x124) == 0)
        return 0;
    return *(long *)(c + 0x690) & mask;
}
