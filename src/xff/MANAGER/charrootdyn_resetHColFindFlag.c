extern void UnlinkSecureParentInfo(char *);

void charrootdyn_resetHColFindFlag(void *character)
{
    UnlinkSecureParentInfo((char *)character + 0xF70);
}
