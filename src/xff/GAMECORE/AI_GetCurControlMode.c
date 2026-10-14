extern void *GetCharacterClass(void *);

int AI_GetCurControlMode(void *actor)
{
    return (*(int *)((char *)(GetCharacterClass(actor)) + 0x750));
}
