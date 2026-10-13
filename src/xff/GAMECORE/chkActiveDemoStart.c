extern int activedemoInfo;

int chkActiveDemoStart(void)
{
    return activedemoInfo & 1;
}
