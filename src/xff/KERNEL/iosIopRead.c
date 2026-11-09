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
extern char B_0004E598[];
extern void (*D_00040590)(void);
extern void (*D_00040594)(void);
extern int sceCdReadIOPm(unsigned int, int, int, int);
extern int sceCdDiskReady(int);
extern int sceCdStatus(void);
extern int sceCdSearchFile(CdFile *, char *);
extern int sceCdSync(int);
extern int sceCdGetError(void);
extern void DelayThread(int);
extern void LoaderSysFSeek64(int, unsigned long, int);
extern void LoaderSysFRead(int, void *, int);
extern void iosEE2IopRequest(void *, int, int, int *);
extern int iosEE2IopEndChk(int);

void iosIopRead(unsigned int lsn, int sectors, int buf)
{
    CdFile file;
    char tmp[0x2000];
    int id;
    int cnt;
    int st;
    int left;
    int n;
    unsigned int base;

    if (B_00046558 == 0) {
        base = B_00046554 + lsn;
retry:
        {
            if (sceCdReadIOPm(base, sectors, buf, B_0004654C) == 0) {
                cnt = 0;
                while (sceCdDiskReady(1) != 2) {
                    st = sceCdStatus();
                    if (st == 0) {
                        cnt++;
                    }
                    if (st == 1 || cnt >= 5) {
                        if (D_00040590 != 0) {
                            D_00040590();
                        }
                        do {
                            do {
                                sceCdDiskReady(0);
                            } while (sceCdSearchFile(&file, B_0004E598) == 0);
                        } while (B_00046554 != file.lsn);
                        if (D_00040594 != 0) {
                            D_00040594();
                        }
                    }
                    DelayThread(0x823);
                }
                goto retry;
            }
            sceCdSync(0);
            if (sceCdGetError() != 0) {
                goto retry;
            }
        }
    } else {
        left = sectors << 11;
        LoaderSysFSeek64(B_0004655C, (unsigned long)lsn << 11, 0);
        while (left > 0) {
            n = left < 0x2001 ? left : 0x2000;
            LoaderSysFRead(B_0004655C, tmp, n);
            iosEE2IopRequest(tmp, buf, n, &id);
            while (iosEE2IopEndChk(id) == 0) {
            }
            left -= n;
            buf += n;
        }
    }
}
