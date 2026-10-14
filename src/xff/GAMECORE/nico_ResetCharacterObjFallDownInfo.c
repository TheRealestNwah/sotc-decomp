extern void *GetCharacterClass(void *);
extern int ResetCharacterClassFallDownInfo(void *);

int nico_ResetCharacterObjFallDownInfo(void *actor)
{
    return ResetCharacterClassFallDownInfo(GetCharacterClass(actor));
}
