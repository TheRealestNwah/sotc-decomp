typedef struct {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
} SemaParam;

typedef struct {
    char pad0[0x24];
    void *serve;
    char pad28[8];
} SifClientData;

typedef struct {
    int id;
    int state;
    char pad8[0x3C];
} NetSlot;

extern int LoaderSysCheckCDBootMode(void);
extern void LoaderSysInitTCP(void);
extern int CreateSema(SemaParam *);
extern void sceSifInitRpc(int);
extern void iosLoadIopModule(const char *, const char *, int, int);
extern int sceSifBindRpc(SifClientData *, int, int);

extern int D_000407F0;
extern SifClientData B_00050880;
extern int B_000508A8;
extern NetSlot B_000508B0[];
extern char RO_00042668[];
extern char RO_00042690[];

int InitNet(void)
{
    SemaParam sp;
    int mode;
    int j;
    int i;
    NetSlot *p;

    mode = LoaderSysCheckCDBootMode();
    D_000407F0 = mode;
    switch (mode) {
    case 1:
        LoaderSysInitTCP();
        for (i = 0; i < 10; i++) {
            p = &B_000508B0[i];
            p->state = 0;
            p->id = -1;
        }
        break;
    case 2:
        break;
    case 0:
    default:
        sp.attr = 0;
        sp.initCount = 1;
        sp.maxCount = 1;
        B_000508A8 = CreateSema(&sp);
        sceSifInitRpc(0);
        iosLoadIopModule(RO_00042668, RO_00042690, 0, 0);
        while (1) {
            if (sceSifBindRpc(&B_00050880, 0x7FFFFFFE, 0) < 0) {
                while (1);
            }
            if (B_00050880.serve != 0) {
                break;
            }
            {
                int k = -1;
                for (j = 0xFFFF; j != k; j -= 4);
            }
        }
        break;
    }
    return 1;
}
