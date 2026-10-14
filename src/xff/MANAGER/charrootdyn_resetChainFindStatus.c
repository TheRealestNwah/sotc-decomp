extern int UnlinkSecureParentInfo();

int charrootdyn_resetChainFindStatus(int a, int b, int c, int d)
{
    return UnlinkSecureParentInfo(a + 3488, b, c, d);
}
