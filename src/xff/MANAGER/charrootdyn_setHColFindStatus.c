extern void LinkSecureParentInfoByGP(int, int);
extern void UnlinkSecureParentInfo(int);

void charrootdyn_setHColFindStatus(void *arg0, int arg1, float fparg0)
{
    int temp_s0;

    temp_s0 = arg0 + 0xF70;
    UnlinkSecureParentInfo(temp_s0);
    LinkSecureParentInfoByGP(temp_s0, arg1);
    (*(float *)((char *)(arg0) + 0xFC0)) = fparg0;
}
