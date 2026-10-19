typedef struct { int sector; int unknown; } FileEntry;
extern FileEntry *B_001517FC;
extern void iosCdStStart(int);
extern void iosCdStRead(void *, int);
extern void iosCdStStop(void);
static inline FileEntry *fileEntry(int file)
{
    return &B_001517FC[file];
}
void sheetFsLoadDirectFile(int file, int offset, void *destination, int size)
{
    int sector = offset / 2048;
    int skip = offset % 2048;
    iosCdStStart(fileEntry(file)->sector + sector);
    if (skip) {
        char discarded[skip];
        iosCdStRead(discarded, skip);
    }
    iosCdStRead(destination, size);
    iosCdStStop();
}