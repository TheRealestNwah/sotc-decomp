typedef struct {
    int offset;
    int size;
} FileEntry;

extern FileEntry *B_001517FC;

int sheetFsGetDirectFileSize(int i)
{
    return *(int *)((char *)B_001517FC + (i << 3) + 4);
}
