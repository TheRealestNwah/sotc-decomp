void CancelCharacterClassMotionChange(char *p)
{
    *(char *)(p + 0xC40) = 0;
    *(char *)(p + 0xC4C) = 0;
    *(int *)(p + 0xC50) = 0;
}
