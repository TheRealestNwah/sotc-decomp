extern int GetCharacterClass();
extern int ResetCharacterClassFallDownInfo();

int nico_ResetCharacterObjFallDownInfo(void)
{
    return ResetCharacterClassFallDownInfo(GetCharacterClass());
}
