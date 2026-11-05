#ifdef NONMATCHING
extern int B_00151860;
extern char *B_00155468[2];
extern char *B_00155470[8];
extern char RO_0011BA70[];

extern void WaitSema(int);
extern void SignalSema(int, int);
extern void iosJumpRecoverPoint(const char *, ...);

void sheetMgrNopSegmentIndex(int *flag)
{
    char *entry;
    char **list;

    WaitSema(B_00151860);
    entry = B_00155468[0];
    if (entry) {
        char *next = *(char **)(entry + 0x2C);

        B_00155468[0] = next;
        if (next == 0)
            B_00155468[1] = 0;
    }
    if (entry == 0)
        iosJumpRecoverPoint(RO_0011BA70);
    *(unsigned int *)(entry + 4) &= ~1;
    list = &B_00155470[2];
    *(int *)entry = 9;
    *(int **)(entry + 0x28) = flag;
    if (flag)
        *flag = 0xDEAD;
    *(int *)(entry + 0x2C) = 0;
    if (list[1] == 0)
        B_00155470[2] = entry;
    else
        *(char **)(list[1] + 0x2C) = entry;
    list[1] = entry;
    SignalSema(B_00151860, 9);
}
#endif
