extern void UnlinkSecureParentInfo(char *);

void charrootdyn_resetChainFindStatus(void *character)
{
    UnlinkSecureParentInfo((char *)character + 0xDA0);
}
