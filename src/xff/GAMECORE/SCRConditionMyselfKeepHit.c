extern void *GetCharacterClass();

int SCRConditionMyselfKeepHit(void)
{
    return (*(int *)((char *)(GetCharacterClass()) + 0xFF0));
}
