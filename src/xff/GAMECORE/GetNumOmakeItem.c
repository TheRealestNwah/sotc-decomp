extern int *DldSysUndefSymbol;
extern int SH_ItemMenuDEFAULT[];
extern int getGameHardMode(void);
extern int MakeStrHashValue(const char *);
extern int _omakeGetFlagChk(int);

typedef struct {
    int a;
    int hash;
    int hashHard;
    char padC[0xC];
    int flag;
    int pad1C;
} OmakeItem;

int GetNumOmakeItem(void)
{
    int *sh = DldSysUndefSymbol != SH_ItemMenuDEFAULT ? SH_ItemMenuDEFAULT : 0;
    int cnt = sh[3];
    OmakeItem *it = (OmakeItem *)sh[4];
    int n = 0;
    int i;

    for (i = 0; i < cnt; i++) {
        int h;

        if (getGameHardMode())
            h = it[i].hashHard;
        else
            h = it[i].hash;
        if (h != MakeStrHashValue("0") && _omakeGetFlagChk(it[i].flag))
            n++;
    }
    return n;
}
