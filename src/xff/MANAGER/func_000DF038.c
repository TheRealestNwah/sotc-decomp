extern int LoaderSysCheckCDBootMode(void);
extern int dsysRead(int fd, void *buffer, int size);
extern void iosJumpRecoverPoint(const char *, ...);
extern int D_00139EF8;
extern char B_00150768[];
extern char B_001507A8[];
extern int B_001507AC;
extern int B_001507B0;

static inline int recvAll(int fd, char *buf, int size)
{
    int got;
    int r;

    got = 0;
    if (LoaderSysCheckCDBootMode() == 1) {
        dsysRead(fd, buf + got, size);
        return 0;
    }
    while (size > 0) {
        r = dsysRead(fd, buf + got, size);
        if (r < 0) {
            return -1;
        }
        size -= r;
        got += r;
    }
    return 0;
}

static void func_000DF038(char *hdr, void (*func)(int, char *))
{
    char *name = B_00150768;
    int fd = D_00139EF8;
    int size;

    if (recvAll(fd, hdr, 12) != 0) {
        iosJumpRecoverPoint("recvFIFO:%s fifo packet header recv error\n", name);
    }
    size = *(int *)(hdr + 8);
    if (size != 0) {
        B_001507AC = 0;
        B_001507B0 = size;
        recvAll(fd, B_001507A8, size < 2 ? size : 1);
        if (func == 0) {
            iosJumpRecoverPoint("recvFIFO: readFunc not entry");
        }
        func(fd, hdr);
    }
}
