struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};

struct SifClientData {
    char unk0[0x24];
    void *serve;
};

extern int CreateSema(struct SemaParam *param);
extern int printf(const char *format, ...);
extern void sceSifInitRpc(unsigned int mode);
extern int sceSifBindRpc(struct SifClientData *cd, unsigned int request, unsigned int mode);
extern int D_0013A188;
extern struct SifClientData D_0013EAC0;
extern char D_00137410[];
extern char D_00137428[];

int usbSerialSysInit(void) {
    struct SemaParam param;
    int i;
    int end;

    param.initCount = 1;
    param.maxCount = 1;
    D_0013A188 = CreateSema(&param);
    if (D_0013A188 == -1) {
        printf(D_00137410);
        while (1) {
            __asm__ volatile("nop");
            __asm__ volatile("nop");
            __asm__ volatile("nop");
            __asm__ volatile("nop");
            __asm__ volatile("nop");
        }
    }
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(&D_0013EAC0, 0x80000220, 0) < 0) {
            printf(D_00137428);
            while (1) {
                __asm__ volatile("nop");
                __asm__ volatile("nop");
                __asm__ volatile("nop");
                __asm__ volatile("nop");
                __asm__ volatile("nop");
            }
        }
        if (D_0013EAC0.serve != 0) {
            break;
        }
        end = -1;
        i = 0xFFFF;
        do {
            i -= 4;
            __asm__ volatile("nop");
            __asm__ volatile("nop");
            __asm__ volatile("nop");
            __asm__ volatile("nop");
            __asm__ volatile("nop");
        } while (i != end);
    }
    return 0;
}

