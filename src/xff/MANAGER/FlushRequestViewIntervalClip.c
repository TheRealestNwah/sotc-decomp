extern void *GetCharacterClass();

void FlushRequestViewIntervalClip(void)
{
    (*(float *)((char *)(GetCharacterClass()) + 0x116C)) = -1.0f;
}
