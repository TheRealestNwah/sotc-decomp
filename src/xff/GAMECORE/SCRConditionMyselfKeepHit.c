extern void *GetCharacterClass(void *);

int SCRConditionMyselfKeepHit(void *actor)
{
    return (*(int *)((char *)(GetCharacterClass(actor)) + 0xFF0));
}
