typedef struct {
    int id;
    int handle;
    char data[0x3C];
} NetSlot;

extern int D_000407F0;
extern int B_0004F880;
extern char B_0004F884[];
extern char B_00050880[];
extern volatile int B_000508A8;
extern NetSlot B_000508B0[];

extern int sceInetRecv(void *, int, int, void *, int, int *, int);
extern int WaitSema(int);
extern int SignalSema(int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern void *memcpy(void *, const void *, int);

/* Parked: Parked: 66 words differ (RPC and slot address hoisting order, like iosNetRecvMsg) */
#ifdef NONMATCHING
int iosNetRecvMsgWithStateCallback(int sock, char *buf, int len, int timeout, void *ctx, void (*cb)(void *, int, int))
{
    int remain = len;

    while (remain > 0) {
        int n;
        int size;

        if (D_000407F0) {
            int flags;
            size = remain;
            if (remain > 0x700) {
                size = 0x700;
            }
            flags = 0;
            n = sceInetRecv(B_000508B0[sock].data, B_000508B0[sock].handle, B_000508B0[sock].id, buf, size, &flags, timeout);
        } else {
            size = remain;
            if (remain > 0xF00) {
                size = 0xF00;
            }
            B_0004F880 = sock;
            *(int *)B_0004F884 = size;
            WaitSema(B_000508A8);
            sceSifCallRpc(B_00050880, 2, 0, &B_0004F880, 8, &B_0004F880, size + 4, 0, 0);
            SignalSema(B_000508A8);
            n = B_0004F880;
            memcpy(buf, B_0004F884, size);
        }
        if (n < 0) {
            return n;
        }
        if (n == 0) {
            break;
        }
        buf += n;
        remain -= n;
        if (ctx != 0 && cb != 0) {
            cb(ctx, len - remain, len);
        }
    }
    return len - remain;
}
#else
extern int iosNetRecvMsgWithStateCallback(int sock, char *buf, int len, int timeout, void *ctx, void (*cb)(void *, int, int));
#endif
