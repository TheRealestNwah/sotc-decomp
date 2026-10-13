extern void *GetCharacterClass();

int AI_GetCurMotionKind(void)
{
    return (*(int *)((char *)(GetCharacterClass()) + 0x1C0));
}
