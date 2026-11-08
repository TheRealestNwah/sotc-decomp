typedef struct {
    char pad0[0x24];
    void *serve;
} SifClientData;

extern void *memset(void *, int, unsigned int);
extern int sceSifBindRpc(SifClientData *, int, int);
extern void Sg2CtrlEntryTickProcById(int, void (*)(void));
extern void Sg2RemoteTickProc(void);

extern char B_000D9280[];
extern int B_000D9240;
extern int B_000D9244;
extern SifClientData B_000DD440;
extern char B_000DD480[];
extern int B_000DD468;
extern int B_000DD46C;

int Sg2RemoteInit(void)
{
    int i;

    memset(B_000D9280, 0, 0x2000);
    B_000D9240 = 0;
    B_000D9244 = 0;
    memset(B_000DD480, 0, 0x280);
    B_000DD468 = B_000DD46C = 0;
    do {
        if (sceSifBindRpc(&B_000DD440, 0x11223344, 0) < 0)
            return -1;
        i = 10000;
        do {
            i -= 625;
            __asm__ volatile("nop");
        } while (i > 0);
    } while (B_000DD440.serve == 0);
    Sg2CtrlEntryTickProcById(4, Sg2RemoteTickProc);
    return 0;
}
