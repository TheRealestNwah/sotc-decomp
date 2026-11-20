typedef struct DsysFile {
    int descriptor;
    int type;
    int unknown08;
    struct DsysFile *next;
} DsysFile;
typedef struct {
    char *name;
    int unk4;
    int unk8;
} CsvMember;
extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
extern void iosFree(void *);
extern int iosSPrintf(char *, const char *, ...);
extern void iosJumpRecoverPoint(const char *, ...);
extern int LoaderSysFWrite(int, void *, int);
extern char *strcat(char *, const char *);
extern char *strcpy(char *, const char *);
extern unsigned int strlen(const char *);
extern char RO_001416D0[];

/* Parked: 13 differing words (register allocation). */
#ifdef NONMATCHING
int WriteMemberCsvModChkTempFile(DsysFile *f, int n, CsvMember *m)
{
    char tmp[0x80];
    char e[] = "";
    int pass;
    char *buf = 0;
    int len = 0;
    int i;
    int ret;
    int wlen;


    for (pass = 0; pass < 2; pass++) {
        if (pass == 1) {
            if (buf != 0)
                __asm__ __volatile__("break 0");
            else
                buf = iosMallocAlign(rootPtn, len, 0x10);
            *buf = e[0];
        }
        for (i = -1; i < n; i++) {
            if (i == -1)
                strcpy(tmp, "MEMBER:");
            else if (i != n - 1)
                iosSPrintf(tmp, "%s,", m[i].name);
            else
                iosSPrintf(tmp, "%s\n", m[i].name);
            if (pass == 0)
                len += strlen(tmp) + 2;
            else
                strcat(buf, tmp);
        }
    }
    ret = -1;
    wlen = strlen(buf);
    if (f->type == 0)
        ret = LoaderSysFWrite(f->descriptor, buf, wlen);
    else
        iosJumpRecoverPoint(RO_001416D0);
    ret = ret >= 0;
    if (buf != 0)
        iosFree(buf);
    return ret;
}
#endif
