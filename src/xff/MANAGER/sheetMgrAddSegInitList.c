extern char *B_00151850;
extern char *B_00151854;
void sheetMgrAddSegInitList(char *p)
{
    *(char **)(p + 0x50) = 0;
    if (B_00151850 != 0)
        *(char **)(B_00151854 + 0x50) = p;
    else
        B_00151850 = p;
    B_00151854 = p;
}
