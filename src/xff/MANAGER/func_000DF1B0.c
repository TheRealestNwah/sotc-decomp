extern int _dsysOpen(const char *name, int type, int mode);
extern int dsysWrite(int fd, void *buffer, int size);
extern void iosJumpRecoverPoint(const char *, ...);
extern void iosFree(void *);
extern int D_00139EF4;
extern int D_00139EF8;
extern int D_00139EFC;
extern char B_00150728[];
extern char B_00150768[];
extern char RO_001417A8[]; /* "nicosysdBoot:%s fifo file not open" */
extern char RO_00141850[]; /* "sendFIFO:%s fifo packet header send error" */
extern char RO_00141880[]; /* "sendFIFO:%s fifo send data error" */
extern char RO_00141948[]; /* "not boot nicosysd" */

static inline int openFIFO(void)
{
    if (D_00139EFC != 0) {
        if (D_00139EF4 != 0) {
            return 1;
        }
        D_00139EF4 = _dsysOpen(B_00150728, 0, 2);
        if (D_00139EF4 == 0) {
            iosJumpRecoverPoint(RO_001417A8, B_00150728);
        }
        D_00139EF8 = _dsysOpen(B_00150768, 0, 1);
        if (D_00139EF8 == 0) {
            iosJumpRecoverPoint(RO_001417A8, B_00150768);
        }
        return 0;
    }
    return -1;
}

static inline int sendAll(int fd, char *buf, int size)
{
    int sent;
    int r;

    sent = 0;
    while (size > 0) {
        r = dsysWrite(fd, buf + sent, size);
        if (r < 0) {
            return -1;
        }
        size -= r;
        sent += r;
    }
    return 0;
}

static inline void sendFIFO(char *name, int fd, char *pkt)
{
    char *data;
    int size;

    data = *(char **)(pkt + 0xC);
    if (sendAll(fd, pkt, 12) != 0) {
        iosJumpRecoverPoint(RO_00141850, name);
    }
    size = *(int *)(pkt + 8);
    if (size != 0) {
        if (sendAll(fd, data, size) != 0) {
            iosJumpRecoverPoint(RO_00141880, name);
        }
    }
}

static void func_000DF1B0(char *pkt)
{
    if (openFIFO() < 0) {
        iosJumpRecoverPoint(RO_00141948);
    }
    sendFIFO(B_00150728, D_00139EF4, pkt);
    iosFree(*(void **)(pkt + 0xC));
}
