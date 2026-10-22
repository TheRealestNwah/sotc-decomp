typedef struct {
    char *buf;
    int port;
    int type;
    int slot;
    int unk10;
    char pad[0x14];
} McPortEx;
extern McPortEx B_0004F800[];
extern char B_0004F600[2][0x100];
extern char RO_000425D8[];
extern void LoaderSysPrintf(const char *, ...);
extern void func_000045C0(void);
extern void iosLoaderResetEntry(void (*)(void));
extern int sceMc2Init(int);
extern int sceMc2CreateSocket(int *, char *);
extern int sceMc2Sync(int, int);

void iosMcInit(void)
{
    int i;
    char *buf;
    McPortEx *p;

    for (i = 1; i >= 0; i--)
        B_0004F800[i].port = -1;
    iosLoaderResetEntry(func_000045C0);
    if (sceMc2Init(0))
        LoaderSysPrintf(RO_000425D8);
    for (i = 0; i < 2; i++) {
        p = &B_0004F800[i];
        buf = B_0004F600[i];
        p->buf = buf;
        p->type = 2;
        p->slot = i == 0 ? 2 : 3;
        p->unk10 = 0;
        p->port = sceMc2CreateSocket(&p->type, buf);
        sceMc2Sync(0, 0);
    }
}
