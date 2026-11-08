typedef struct {
    int id;
    int handle;
    char data[0x3C];
} NetSlot;

extern int D_000407F0;
extern int B_0004F880[];
extern char B_00050880[];
extern volatile int B_000508A8;
extern NetSlot B_000508B0[];

extern int sceInetRecv(void *, int, int, void *, int, int *, int);
extern int WaitSema(int);
extern int SignalSema(int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern void *memcpy(void *, const void *, int);


#ifdef NONMATCHING
/* Parked: 82 words differ (slot and RPC buffer address hoisting, 6 words short) */
int iosNetRecvMsg(int sock, char *buf, int len, int timeout)
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
            B_0004F880[0] = sock;
            B_0004F880[1] = size;
            WaitSema(B_000508A8);
            sceSifCallRpc(B_00050880, 2, 0, B_0004F880, 8, B_0004F880, size + 4, 0, 0);
            SignalSema(B_000508A8);
            n = B_0004F880[0];
            memcpy(buf, &B_0004F880[1], size);
        }
        if (n < 0) {
            return n;
        }
        if (n == 0) {
            break;
        }
        remain -= n;
        buf += n;
    }
    return len - remain;
}
#endif
