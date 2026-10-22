typedef struct {
    char pad0[0x20];
    int port;
    int slot;
    int reserved;
    int offset;
    int used;
} McFile;

extern void LoaderSysPrintf(const char *, ...);
extern int iosMcReadFile(int, int, McFile *, void *, int, int);
extern int iosMcWriteFile(int, int, McFile *, void *, int, int);

int mcWrite(McFile *file, void *buf, int size)
{
    int result;
    file->used += size;
    if (file->reserved < file->used) {
        LoaderSysPrintf("mcWrite:\x1b[31m reserve size over \x1b[m\n");
        __asm__ __volatile__("break 0");
    }
    result = iosMcWriteFile(file->port, file->slot, file, buf, file->offset, size);
    file->offset += size;
    return result;
}

int mcRead(McFile *file, void *buf, int size)
{
    int result;
    file->used += size;
    if (file->reserved < file->used)
        LoaderSysPrintf("mcRead:\x1b[31m reserve size over \x1b[m\n");
    result = iosMcReadFile(file->port, file->slot, file, buf, file->offset, size);
    file->offset += size;
    return result;
}
