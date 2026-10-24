extern void UnlinkSecureParentInfo(char *);

void ResetCharacterClassPositionMemoryInfo(void *character)
{
    UnlinkSecureParentInfo((char *)character + 0x1020);
}
