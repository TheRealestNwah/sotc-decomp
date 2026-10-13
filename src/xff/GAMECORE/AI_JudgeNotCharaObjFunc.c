extern int GetCharacterClass();

int AI_JudgeNotCharaObjFunc(void)
{
    return GetCharacterClass() == 0;
}
