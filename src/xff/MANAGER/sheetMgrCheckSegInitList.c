typedef struct SheetInitEntry {
    char pad[0x50];
    struct SheetInitEntry *next;
} SheetInitEntry;

extern SheetInitEntry *B_00151850;

int sheetMgrCheckSegInitList(SheetInitEntry *entry)
{
    SheetInitEntry *node = B_00151850;
    int found = 0;

    while (node != 0) {
        if (node == entry) {
            found = 1;
            break;
        }
        node = node->next;
    }
    return found;
}
