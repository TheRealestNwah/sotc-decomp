extern void *GetCharacterClass();

int AI_GetCurControlMode(void)
{
    return (*(int *)((char *)(GetCharacterClass()) + 0x750));
}
