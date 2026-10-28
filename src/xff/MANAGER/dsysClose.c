typedef struct DsysFile {
    int descriptor;
    int type;
    int unknown08;
    struct DsysFile *next;
} DsysFile;
extern DsysFile *B_001502EC;
extern DsysFile *B_001502F0;
extern int LoaderSysFClose(int);
extern void iosJumpRecoverPoint(void *);
extern unsigned char RO_00141690[];

void dsysClose(DsysFile *file)
{
    DsysFile *current;
    DsysFile *previous;
    if (file->type == 0)
        LoaderSysFClose(file->descriptor);
    else
        iosJumpRecoverPoint(RO_00141690);
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
    {
        if (previous != 0)
            previous->next = current->next;
        else
            B_001502F0 = current->next;
        file->next = B_001502EC;
        B_001502EC = file;
    }
}
