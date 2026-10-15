typedef struct DsysFile { int a, b, c; struct DsysFile *next; } DsysFile;
extern DsysFile *B_001502EC;
extern int B_001502F0;
extern DsysFile dsysFileList[];

void dsysFileInit(void)
{
    int i;
    B_001502F0 = 0;
    B_001502EC = 0;
    for (i = 0; i < 8; i++) {
        dsysFileList[i].next = B_001502EC;
        B_001502EC = &dsysFileList[i];
    }
}
