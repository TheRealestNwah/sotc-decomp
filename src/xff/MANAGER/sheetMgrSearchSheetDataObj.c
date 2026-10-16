extern char **D_00139F10;
extern void iosJumpRecoverPoint(const char *, int);

char *sheetMgrSearchSheetDataObj(int idx, int hash)
{
    char *s = D_00139F10[idx];
    char *o;

    if (s == 0)
        iosJumpRecoverPoint(__FUNCTION__ "sheet header %s not found", **(int **)(s + 0x38));
    for (o = *(char **)(s + 0x40); o != 0; o = *(char **)(o + 0x54)) {
        if (hash == (*(int **)(o + 0x38))[1])
            break;
    }
    return o;
}
