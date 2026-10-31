typedef struct DsysFile {
    int descriptor;
    int type;
    int unknown08;
    struct DsysFile *next;
} DsysFile;
extern DsysFile *B_001502EC;
extern DsysFile *B_001502F0;
extern int iosSPrintf(char *, const char *, ...);
extern int func_000DDE48(int *fd, const char *name, int mode);

static inline DsysFile *allocFile(void)
{
    DsysFile *file;

    file = B_001502EC;
    if (file != 0) {
        B_001502EC = file->next;
        file->next = B_001502F0;
        B_001502F0 = file;
    }
    return file;
}

static inline void freeFile(DsysFile *file)
{
    DsysFile *current;
    DsysFile *previous;

    previous = 0;
    current = B_001502F0;
    if (current == 0)
        return;
    for (;;) {
        if (file == current)
            goto found;
        previous = current;
        current = current->next;
        if (current == 0)
            break;
    }
    return;
found:
    if (previous != 0)
        previous->next = current->next;
    else
        B_001502F0 = current->next;
    file->next = B_001502EC;
    B_001502EC = file;
}

DsysFile *OpenCsvModChkTempFile(char *name)
{
    char path[0xD0];
    DsysFile *file;
    int mode;
    DsysFile *result;

    iosSPrintf(path, "%s.tmp", name);
    mode = 0x602;
    file = allocFile();
    if (file == 0)
        return 0;
    file->type = 0;
    file->unknown08 = 0x602;
    result = file;
    if (func_000DDE48(&result->descriptor, path, mode) < 0)
        result = 0;
    if (result == 0)
        freeFile(file);
    return result;
}
