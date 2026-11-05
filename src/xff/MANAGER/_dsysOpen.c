typedef struct DsysFile {
    int descriptor;
    int type;
    int unknown08;
    struct DsysFile *next;
} DsysFile;
extern DsysFile *B_001502EC;
extern DsysFile *B_001502F0;
extern int func_000DDE48(int *fd, const char *name, int mode);
extern void iosJumpRecoverPoint(const char *);

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

DsysFile *_dsysOpen(const char *name, int type, int mode)
{
    DsysFile *file;
    DsysFile *result;

    file = allocFile();
    if (file == 0)
        return 0;
    file->unknown08 = mode;
    file->type = type;
    result = file;
    if (type == 0) {
        if (func_000DDE48(&result->descriptor, name, mode) < 0)
            result = 0;
    } else {
        iosJumpRecoverPoint("open dev code error
");
    }
    if (result == 0)
        freeFile(file);
    return result;
}
