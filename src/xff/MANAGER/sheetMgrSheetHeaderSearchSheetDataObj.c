typedef struct SheetDataObj {
    char pad0[0x38];
    int *header;
    char pad3C[0x18];
    struct SheetDataObj *next;
} SheetDataObj;

SheetDataObj *sheetMgrSheetHeaderSearchSheetDataObj(char *mgr, int id)
{
    SheetDataObj *obj = *(SheetDataObj **)(mgr + 0x40);

    while (obj != 0 && id != obj->header[1]) {
        obj = obj->next;
    }
    return obj;
}
