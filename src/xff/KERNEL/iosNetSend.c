#ifdef NONMATCHING
/* Parked: 57 words differ (register allocation, rpc arg setup order) */
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
        return sceInetSend(&B_000508B8[id], B_000508B8[id - 1].sock, B_000508B8[id - 1].len, buf, len, &r, flags);
    }
    B_0004F880[0] = id;
    B_0004F880[1] = len;
    memcpy(&B_0004F880[2], buf, len);
    WaitSema(B_000508A8);
    sceSifCallRpc(B_00050880, 3, 0, B_0004F880, len + 8, B_0004F880, 4, 0, 0);
    SignalSema(B_000508A8);
    return B_0004F880[0];
}
#endif
