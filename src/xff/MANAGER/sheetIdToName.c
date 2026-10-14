extern char **D_00139F10;

int sheetIdToName(int i)
{
    return **(int **)(D_00139F10[i] + 0x38);
}
