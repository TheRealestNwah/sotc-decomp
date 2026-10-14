int GetCharacterClassCurAnimationFrameRate(char *p)
{
    char *a = *(char **)(p + 0x1C0);

    if (a == 0) {
        return 0;
    }
    return *(int *)(a + 0x5C);
}
