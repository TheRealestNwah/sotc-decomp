struct UsbSerialBlock {
    char data[0x40];
};

struct UsbSerialSend {
    char data[0xFC];
    int unkFC;
};

extern int strlen(const char *s);
extern char *strcpy(char *dst, const char *src);
extern int WaitSema(int sema_id);
extern int sceSifCallRpc(void *cd, unsigned int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize,
                         void (*end)(void *), void *earg);
extern void func_001053F0(void *arg);
extern char D_0013EAC0[];
extern struct UsbSerialSend D_0013EB00;
extern int D_0013EB40[];
extern int D_0013A188;

int usbSerialSysPutString(const char *str) {
    int len = strlen(str);
    int n;
    int ret;
    int i;
    char *p;

    while (len > 0) {
        if (len < 0x40) {
            strcpy(D_0013EB00.data, str);
            D_0013EB00.unkFC = 0;
            n = len;
        } else {
            n = 0x40;
            *(struct UsbSerialBlock *)D_0013EB00.data = *(struct UsbSerialBlock *)str;
        }
        p = D_0013EB00.data;
        for (i = 0; i < n; i++, p++) {
            if (*p == '\n') {
                *p = '\r';
            }
        }
        WaitSema(D_0013A188);
        ret = sceSifCallRpc(D_0013EAC0, 0x10, 0, &D_0013EB00, 0x40, D_0013EB40, 0x20, func_001053F0, 0);
        if (ret != 0) {
            return ret;
        }
        len -= n;
        str += n;
    }
    return D_0013EB40[0];
}
