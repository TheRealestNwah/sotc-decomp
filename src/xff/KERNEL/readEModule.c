typedef struct {
    unsigned int lsn;
    int size;
    char name[16];
    unsigned char date[8];
    unsigned int flag;
} CdFile;

extern char RO_00042A10[];
extern char RO_00042A18[];
extern char RO_00042A40[];
extern int strncmp(const char *, const char *, int);
extern char *strstr(const char *, const char *);
extern int sceCdSearchFile(CdFile *, const char *);
extern void iosJumpRecoverPoint(void *, ...);
extern int iosLoaderGetFileSizeName(char *);
extern int func_00008BB0(char *, int, int);

#ifdef NONMATCHING
/* Parked: 9 words differ (register allocation and ordering) */
int readEModule(char *name, int arg)
{
    int result = 0;
    int size;
    CdFile file;

    if (strncmp(name, RO_00042A40, 7) == 0) {
        char *path = strstr(name, RO_00042A10) + 1;

        if (sceCdSearchFile(&file, path) == 0) {
            iosJumpRecoverPoint(RO_00042A18, path);
        }
        size = file.size;
        if (size >= 0) {
            goto read;
        }
    } else {
        int n = iosLoaderGetFileSizeName(name);

        if (n >= 0) {
            size = n;
        read:
            result = func_00008BB0(name, size, arg);
        }
    }
    return result;
}
#endif
