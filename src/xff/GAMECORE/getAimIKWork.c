extern void *GetCharacterClass();

int getAimIKWork(void)
{
    return (*(int *)((char *)(GetCharacterClass()) + 0x1110));
}
