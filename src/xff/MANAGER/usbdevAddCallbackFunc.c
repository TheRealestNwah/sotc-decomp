typedef struct UsbCallback {
    void *func;
    struct UsbCallback *next;
} UsbCallback;

typedef struct {
    UsbCallback *mouse;
    char pad4[0x54];
    UsbCallback *keybd;
} UsbDev;

extern void *iosMallocAlign(void *, int, int);
extern unsigned char rootPtn[];
extern UsbDev B_0014DC10;

void usbdevAddCallbackFunc(void *func, int type)
{
    UsbCallback *cb = iosMallocAlign(rootPtn, 8, 16);
    UsbCallback *p;

    cb->func = func;
    cb->next = 0;
    switch (type) {
    case 0:
        if (B_0014DC10.mouse == 0) {
            B_0014DC10.mouse = cb;
            return;
        }
        p = B_0014DC10.mouse;
        break;
    case 1:
        if (B_0014DC10.keybd == 0) {
            B_0014DC10.keybd = cb;
            return;
        }
        p = B_0014DC10.keybd;
        break;
    default:
        return;
    }
    while (p) {
        if (p->next == 0) {
            p->next = cb;
            break;
        }
        p = p->next;
    }
}
