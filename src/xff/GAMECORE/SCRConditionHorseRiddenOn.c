extern void *GetCharacterClass(void *);

int SCRConditionHorseRiddenOn(int arg0)
{
    return arg0 != (*(int *)((char *)(GetCharacterClass((void *)arg0)) + 0x960));
}
