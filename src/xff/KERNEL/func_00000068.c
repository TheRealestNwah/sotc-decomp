typedef struct {
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    unsigned int flag;
} CdFile;

extern int B_0004654C;
extern int B_00046554;
extern int B_00046558;
extern int B_0004655C;
extern char B_00046580[];
extern unsigned long B_0004E580;
extern unsigned long B_0004E588;
extern char B_0004E598[];
extern void (*D_00040590)(void);
extern void (*D_00040594)(void);
extern int sceCdRead(unsigned int, int, void *, int);
extern int sceCdDiskReady(int);
extern int sceCdStatus(void);
extern int sceCdSearchFile(CdFile *, char *);
extern int sceCdSync(int);
extern int sceCdGetError(void);
extern void DelayThread(int);
extern void LoaderSysFSeek64(int, unsigned long, int);
extern void LoaderSysFRead(int, void *, int);

#define WAIT_DISC() { \
    CdFile file; \
    int cnt; \
    int st; \
 \
    cnt = 0; \
    while (sceCdDiskReady(1) != 2) { \
        st = sceCdStatus(); \
        if (st == 0) { \
            cnt++; \
        } \
        if (st == 1 || cnt >= 5) { \
            if (D_00040590 != 0) { \
                D_00040590(); \
            } \
            do { \
                do { \
                    sceCdDiskReady(0); \
                } while (sceCdSearchFile(&file, B_0004E598) == 0); \
            } while (B_00046554 != file.lsn); \
            if (D_00040594 != 0) { \
                D_00040594(); \
            } \
        } \
        DelayThread(0x823); \
    } \
}

static void func_00000068(int lsn)
{
    B_0004E580 = (long)lsn << 11;
    if (B_00046558 == 0) {
    retry:
        while (sceCdRead(lsn, 0x10, B_00046580, B_0004654C) != 1) {
            WAIT_DISC()
        }
        sceCdSync(0);
        if (sceCdGetError() != 0) {
            WAIT_DISC()
            goto retry;
        }
    } else {
        LoaderSysFSeek64(B_0004655C, (long)lsn << 11, 0);
        LoaderSysFRead(B_0004655C, B_00046580, 0x8000);
    }
    B_0004E588 = (long)(lsn + 0x10) << 11;
}
