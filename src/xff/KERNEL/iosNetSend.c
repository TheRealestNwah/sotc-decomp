extern int D_000407F0;
typedef struct { char sub[0x3C]; int len; int sock; } NetConn;
extern NetConn B_000508B8[];
extern int B_0004F880[];
extern int B_000508A8;
extern char B_00050880[];
extern void *memcpy(void *, const void *, unsigned int);
extern int sceInetSend(void *, int, int, void *, int, int *, int);
extern int WaitSema(int);
extern int SignalSema(int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);

int iosNetSend(int id, void *buf, int len, int flags)
{
    if (D_000407F0) {
        int r = 0;
        return sceInetSend(&B_000508B8[id], ((int *)((char *)B_000508B8 + id * 0x44))[-1], ((int *)((char *)B_000508B8 + id * 0x44))[-2], buf, len, &r, flags);
    }
    {
        int *b = B_0004F880;
        int *sem = &B_000508A8;
        int l8 = len + 8;
        b[0] = id;
        b[1] = len;
        memcpy(b + 2, buf, len);
        WaitSema(*sem);
        sceSifCallRpc(B_00050880, 3, 0, b, l8, b, 4, 0, 0);
        SignalSema(*sem);
        return *b;
    }
}
