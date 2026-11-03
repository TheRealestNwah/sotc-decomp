typedef struct Ptn Ptn;
typedef struct DsysFile {
    int descriptor;
    int type;
    int unknown08;
    struct DsysFile *next;
} DsysFile;
extern Ptn rootPtn;
extern DsysFile *B_001502EC;
extern DsysFile *B_001502F0;
extern int LoaderSysFClose(int);
extern void iosJumpRecoverPoint(void *);
extern unsigned char RO_00141690[];
extern char RO_00141720[]; /* "%s.tmp", shared with OpenCsvModChkTempFile */
extern int iosSPrintf(char *, const char *, ...);
extern unsigned int strlen(const char *);
extern void nicosysdSendDataStart(void *, int, Ptn *, int);
extern void nicosysdSendDataWrite(void *, void *, int);
extern void nicosysdExec(void *, void *, void *);
extern void nicosysdEchoReadCallBack();

static inline void closeFile(DsysFile *file)
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

static inline void makeTmpName(char *dst, char *name)
{
    iosSPrintf(dst, RO_00141720, name);
}

int CloseCsvModChkTempFile(DsysFile **pfile, char *input, char *name, char *output)
{
    int res[4];
    char buf[0x20];
    char cmd[0xD0];
    char path[0xD0];
    int len;

    closeFile(*pfile);
    *pfile = 0;
    makeTmpName(path, name);
    iosSPrintf(cmd, "csvmodchk %s -i %s -e %s.mod", input, path, output);
    len = strlen(cmd) + 1;
    nicosysdSendDataStart(buf, 0x3EA, &rootPtn, len);
    nicosysdSendDataWrite(buf, cmd, len);
    nicosysdExec(buf, res, nicosysdEchoReadCallBack);
    return 1;
}
