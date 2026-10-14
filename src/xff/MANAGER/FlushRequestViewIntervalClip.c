extern void *GetCharacterClass(void *);

void FlushRequestViewIntervalClip(void *actor)
{
    (*(float *)((char *)(GetCharacterClass(actor)) + 0x116C)) = -1.0f;
}
