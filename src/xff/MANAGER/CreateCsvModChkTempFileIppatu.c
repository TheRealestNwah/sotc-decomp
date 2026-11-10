/* ~121 diffs, 2 words longer (139 vs 137). Builds a csvmodchk temp file: opens it (OpenCsvModChkTempFile), writes the member header, appends one segment per node of the list at t0+0x40 (next at +0x54, segment at +0x38), then closes through CloseCsvModChkTempFile(&file, t0[0x38][0], a0, a1) and returns 1; on any failure it closes the file with the closeFile inline from CloseCsvModChkTempFile.c (LoaderSysFClose or the RO_0011B3F0 recover, then unlinks it from B_001502F0 onto the free list B_001502EC) and returns 0. The Original keeps a1 in $s7 / a0 in $s5 and holds the file pointer in $a0 right after the open call (ours uses $a1 and swaps $s6/$s7). */
typedef struct Ptn Ptn;
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
extern unsigned char RO_0011B3F0[];
extern DsysFile *OpenCsvModChkTempFile(void *, void *, void *, void *);
extern int WriteMemberCsvModChkTempFile(DsysFile *, void *, void *);
extern int AddSegmentCsvModChkTempFile(DsysFile *, void *, void *, void *, void *);
extern int CloseCsvModChkTempFile(DsysFile **, void *, void *, void *);

static inline void closeFile(DsysFile *file)
{
    DsysFile *current;
    DsysFile *previous;
    if (file->type == 0)
        LoaderSysFClose(file->descriptor);
    else
        iosJumpRecoverPoint(RO_0011B3F0);
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

#ifdef NONMATCHING
int CreateCsvModChkTempFileIppatu(void *a0, void *a1, void *a2, void *a3, char *t0, void *t1)
{
    DsysFile *file;
    char *node;

    file = OpenCsvModChkTempFile(a0, a1, a2, a3);
    if (file == 0)
        return (int)file;
    if (WriteMemberCsvModChkTempFile(file, a2, a3) == 0) {
        closeFile(file);
        return 0;
    }
    for (node = *(char **)(t0 + 0x40); node != 0; node = *(char **)(node + 0x54)) {
        if (AddSegmentCsvModChkTempFile(file, t1, *(void **)(node + 0x38), a2, a3) == 0) {
            closeFile(file);
            return 0;
        }
    }
    CloseCsvModChkTempFile(&file, **(void ***)(t0 + 0x38), a0, a1);
    return 1;
}
#endif
