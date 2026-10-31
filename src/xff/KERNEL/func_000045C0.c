typedef struct {
    char *buf;
    int port;
    int type;
    int slot;
    int unk10;
    char pad[0x14];
} McPortEx;
extern McPortEx B_0004F800[];
extern int sceMc2Sync(int, int);
extern int sceMc2DeleteSocket(int);
extern void sceMc2End(void);
extern void LoaderSysPrintf(const char *, ...);

static void func_000045C0(void)
{
    McPortEx *p = B_0004F800;
    int i;
    int ret;

    for (i = 0; i < 2; i++, p++) {
        if (p->port >= 0) {
            sceMc2Sync(0, 0);
            ret = sceMc2DeleteSocket(p->port);
            if (ret != 0) {
                LoaderSysPrintf("iosmc: iosMcEnd: \x1b[31merror close iosport:%d(socket:%d). %d\x1b[m\n", i, p->port, ret);
            }
            p->port = -1;
        }
    }
    sceMc2Sync(0, 0);
    sceMc2End();
}
