extern char *GetCharacterClass(void *);

void *nico_GetPlayerCharacterRidingHorseObject(void *actor)
{
    char *c = GetCharacterClass(actor);
    void *h;
    if (c == 0)
        return 0;
    h = *(void **)(c + 0x950);
    return h == actor ? 0 : h;
}
