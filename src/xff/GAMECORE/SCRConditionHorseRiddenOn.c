extern void *GetCharacterClass();

int SCRConditionHorseRiddenOn(int arg0)
{
    return arg0 != (*(int *)((char *)(GetCharacterClass()) + 0x960));
}
