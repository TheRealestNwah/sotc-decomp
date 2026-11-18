typedef struct {
    int unk0;
    int unk4;
    int size;
    char pad[0x34];
} LoaderStat;

extern int D_00139EF0;
extern char B_001506E8[], B_00150728[];
extern int _dsysOpen(char *, int, int);
extern int dsysClose(int);
extern int dsysWrite(int, void *, int);
extern int iosSPrintf(char *, const char *, ...);
extern int LoaderSysGetstat(char *, LoaderStat *);
extern int memcmp(const void *, const void *, unsigned int);
extern unsigned int strlen(const char *);

void nicosysdRebootRequest(void)
{
    int fd;
    LoaderStat st;
    int left;
    int done;
    int n;
    int i;

    if (D_00139EF0 != 0) {
        fd = _dsysOpen(B_001506E8, 0, 2);
        if (fd != 0) {
            char path[strlen(B_00150728) + 0x20];
            iosSPrintf(path, "host0:%s", B_00150728);
            if (LoaderSysGetstat(path, &st) != 0)
                __asm__ __volatile__("break 0");
            {
                char msg[] = "reboot";
                LoaderStat now;
                left = 7;
                done = 0;
                do {
                    n = dsysWrite(fd, msg + done, left);
                    if (n < 0)
                        break;
                    left -= n;
                    done += n;
                } while (left > 0);
                dsysClose(fd);
                while (LoaderSysGetstat(path, &now) != 0 || memcmp((char *)&st + 0xC, (char *)&now + 0xC, 8) == 0) {
                    i = 999999;
                    do {
                        i -= 4;
                        __asm__ __volatile__("nop");
                    } while (i != -1);
                }
            }
        }
    }
}
