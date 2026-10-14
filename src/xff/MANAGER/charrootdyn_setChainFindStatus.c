extern void LinkSecureParentInfoByGP(void *, int);
extern void UnlinkSecureParentInfo(void *);

void charrootdyn_setChainFindStatus(void *parent, int group)
{
    char *work = (char *)parent + 0xDA0;

    UnlinkSecureParentInfo(work);
    LinkSecureParentInfoByGP(work, group);
}
