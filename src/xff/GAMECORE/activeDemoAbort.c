extern int activedemoInfo[];
extern void activeDemoCancel(int);

void activeDemoAbort(void)
{
    if (activedemoInfo[3] != 0)
        activeDemoCancel(activedemoInfo[2]);
}
