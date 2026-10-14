extern int adpcmOpenChkComplete(int);

int bgmChkStandbyComplete(int *p)
{
    if (p[2] == 1)
        return 0;
    return adpcmOpenChkComplete(p[0]);
}
