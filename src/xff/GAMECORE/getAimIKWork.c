extern void *GetCharacterClass(void *);

int getAimIKWork(void *actor)
{
    return (*(int *)((char *)(GetCharacterClass(actor)) + 0x1110));
}
