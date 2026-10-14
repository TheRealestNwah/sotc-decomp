extern void *GetCharacterClass(void *);

int AI_GetCurMotionKind(void *actor)
{
    return (*(int *)((char *)(GetCharacterClass(actor)) + 0x1C0));
}
