typedef struct {
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    char pad20[0x10];
} CdFile;

extern int strncmp(const char *, const char *, unsigned int);
extern char *strcpy(char *, const char *);
extern int sceCdSearchFile(CdFile *, const char *);
extern int LoaderSysFOpen(char *, int, int);
extern void iosJumpRecoverPoint(const char *, ...);

extern char RO_00041EB0[];
extern char RO_00041EB8[];
extern int B_00046554;
extern int B_00046558;
extern int B_0004655C;
extern long B_0004E580;
extern long B_0004E588;
extern long B_0004E590;
extern char B_0004E598[];

void iosCdStInit(char *name)
{
    CdFile f;

    B_00046558 = strncmp(RO_00041EB0, name, 6) == 0;
    B_0004E590 = B_0004E580 = B_0004E588 = -1;
    if (B_00046558 == 0) {
        if (!sceCdSearchFile(&f, name))
            __asm__ volatile("break 0");
        B_00046554 = f.lsn;
        strcpy(B_0004E598, name);
    } else {
        B_0004655C = LoaderSysFOpen(name, 1, 0x1FF);
        if (B_0004655C < 0)
            iosJumpRecoverPoint(RO_00041EB8, name);
    }
}
