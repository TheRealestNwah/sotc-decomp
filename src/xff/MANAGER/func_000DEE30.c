#ifdef NONMATCHING /* 22 diffs: refill block register allocation (AC in s2 reused as the constant 1, min in s1 via movn, got in s0). Permuter (2 workers, 30 min): no valid improvement. */
extern int LoaderSysCheckCDBootMode(void);
extern int dsysRead(int fd, void *buffer, int size);
extern void iosJumpRecoverPoint(const char *, ...);
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

extern void *memcpy(void *, const void *, unsigned int);

int func_000DEE30(int fd, char *buf, int size)
{
    int done = 0;
    int n;
    int rest;
    int ac;

    if (B_001507B0 < size) {
        iosJumpRecoverPoint("readRecvBuff:recv size over %d < %d\n", B_001507B0, size);
    }
    while (size != 0) {
        n = 1 - B_001507AC;
        n = n < size ? n : size;
        if (n != 0) {
            memcpy(buf + done, B_001507A8 + B_001507AC, n);
            size -= n;
            done += n;
            B_001507AC += n;
            B_001507B0 -= n;
        }
        if (size > 0) {
            recvAll(fd, buf + done, size);
            B_001507B0 -= size;
            size = 0;
        }
        rest = B_001507B0;
        if (rest != 0) {
            ac = B_001507AC;
            if (ac == 1) {
                B_001507AC = 0;
                recvAll(fd, B_001507A8, rest < 2 ? rest : ac);
            }
        }
    }
    return 0;
}
#endif
