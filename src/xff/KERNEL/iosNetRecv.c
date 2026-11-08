extern int D_000407F0;
typedef struct { char sub[0x3C]; int len; int sock; } NetConn;
extern NetConn B_000508B8[];
extern int B_0004F880[];
extern int B_000508A8;
extern char B_00050880[];
extern void *memcpy(void *, const void *, unsigned int);
extern int sceInetRecv(void *, int, int, void *, int, int *, int);
extern int WaitSema(int);
extern int SignalSema(int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);

int iosNetRecv(int id, void *buf, int len, int flags)
{
    int r;
    if (D_000407F0) {
        int rr = 0;
        return sceInetRecv(&B_000508B8[id], ((int *)((char *)B_000508B8 + id * 0x44))[-1], ((int *)((char *)B_000508B8 + id * 0x44))[-2], buf, len > 0x700 ? 0x700 : len, &rr, flags);
    }
    {
        int *b = B_0004F880;
        int *sem = &B_000508A8;
        int n = len > 0xF00 ? 0xF00 : len;
        int *q = b + 1;
        int n4 = n + 4;
        b[0] = id;
        *q = n;
        WaitSema(*sem);
        sceSifCallRpc(B_00050880, 2, 0, b, 8, b, n4, 0, 0);
        SignalSema(*sem);
        r = *b;
        memcpy(buf, q, n);
        return r;
    }
}
