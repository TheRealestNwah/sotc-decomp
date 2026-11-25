typedef struct {
    char *buf;
    int port;
    int type;
    int slot;
    int unk10;
    char pad[0x14];
} McPortEx;
typedef struct { int port; char pad[0x24]; } McPort;
typedef struct { int code; int ret; int pad; } McErr;

extern McPortEx B_0004F800[];
extern McPort B_0004F804[];
extern char B_0004F600[2][0x100];
extern McErr D_000406E8[];
extern char RO_000424F0[];
extern char RO_000425D8[];
extern void LoaderSysPrintf(const char *, ...);
extern void iosLoaderResetEntry(void (*)(void));
extern int sceMc2Init(int);
extern int sceMc2CreateSocket(int *, char *);
extern int sceMc2DeleteSocket(int);
extern int sceMc2Sync(int, int);
extern void sceMc2End(void);
extern int sceMc2GetInfo(int, int *);
extern int sceMc2Chdir(int, int, int);
extern int sceMc2Mkdir(int, int);
extern int sceMc2CreateFile(int, int);
extern int sceMc2Delete(int, int);
extern int sceMc2ReadFile(int, int, int, int, int);
extern int sceMc2WriteFile(int, int, int, int, int);
extern int sceMc2Format(int);
extern int sceMc2Unformat(int);
extern int sceMc2GetDir(int, int, int, int, int, int);

static void func_000045C0(void);

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

int iosMcGetInfo(int port, int verbose, int *out)
{
    int buf[4];
    int r;
    int prev;
    int retry;
    McPortEx *p;
    McErr *e;
    int ret;
    unsigned int i;

    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    prev = 0;
    retry = 0;
    p = &B_0004F800[port];
    do {
        r = sceMc2GetInfo(p->port, buf) & 0xFFFF;
        *out = buf[2];
        switch (r) {
        case 0:
        case 0x13:
        case 0x9003:
            retry = 0;
            break;
        default:
            {
                int t = 8;
                if (r == prev)
                    t = retry;
                retry = t;
            }
            prev = r;
            break;
        }
        {
            int t = retry - 1;
            retry = t;
            if (t <= 0)
                break;
        }
    } while (1);
    ret = 8;
    e = D_000406E8;
    i = 0;
    do {
        if (r == e->code) {
            ret = e->ret;
            break;
        }
        i++;
        e++;
    } while (i < 22);
    return ret;
}

int iosMcChDir(int port, int verbose, int dir)
{
    unsigned int i;
    int code;
    int ret;
    McErr *e;

    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    code = sceMc2Chdir(B_0004F804[port].port, dir, 0) & 0xFFFF;
    ret = 8;
    e = D_000406E8;
    i = 0;
    do {
        if (code == e->code) {
            ret = e->ret;
            break;
        }
        i++;
        e++;
    } while (i < 0x16);
    return ret;
}

int iosMcMkDir(int port, int verbose, int name)
{
    unsigned int i;
    int code;
    int ret;
    McErr *e;

    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    code = sceMc2Mkdir(B_0004F804[port].port, name) & 0xFFFF;
    ret = 8;
    e = D_000406E8;
    i = 0;
    do {
        if (code == e->code) {
            ret = e->ret;
            break;
        }
        i++;
        e++;
    } while (i < 0x16);
    return ret;
}

int iosMcCreateFile(int port, int verbose, int name)
{
    unsigned int i;
    int code;
    int ret;
    McErr *e;

    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    code = sceMc2CreateFile(B_0004F804[port].port, name) & 0xFFFF;
    ret = 8;
    e = D_000406E8;
    i = 0;
    do {
        if (code == e->code) {
            ret = e->ret;
            break;
        }
        i++;
        e++;
    } while (i < 0x16);
    return ret;
}

int iosMcDeleteFile(int port, int verbose, int name)
{
    unsigned int i;
    int code;
    int ret;
    McErr *e;

    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    code = sceMc2Delete(B_0004F804[port].port, name) & 0xFFFF;
    ret = 8;
    e = D_000406E8;
    i = 0;
    do {
        if (code == e->code) {
            ret = e->ret;
            break;
        }
        i++;
        e++;
    } while (i < 0x16);
    return ret;
}

int iosMcReadFile(int port, int verbose, int a, int b, int c, int d)
{
    unsigned int i;
    int code;
    int r;
    int ret;

    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    r = sceMc2ReadFile(B_0004F804[port].port, a, b, c, d);
    if (r >= 0)
        return 0;
    code = r & 0xFFFF;
    ret = 8;
    i = 0;
    do {
        if (code == D_000406E8[i].code) {
            ret = D_000406E8[i].ret;
            break;
        }
        i++;
    } while (i < 0x16);
    return ret;
}

int iosMcWriteFile(int port, int verbose, int a, int b, int c, int d)
{
    unsigned int i;
    int code;
    int r;
    int ret;

    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    r = sceMc2WriteFile(B_0004F804[port].port, a, b, c, d);
    if (r >= 0)
        return 0;
    code = r & 0xFFFF;
    ret = 8;
    i = 0;
    do {
        if (code == D_000406E8[i].code) {
            ret = D_000406E8[i].ret;
            break;
        }
        i++;
    } while (i < 0x16);
    return ret;
}

int iosMcFormat(int port, int verbose)
{
    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    return sceMc2Format(B_0004F804[port].port);
}

int iosMcUnformat(int port, int verbose)
{
    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    return sceMc2Unformat(B_0004F804[port].port);
}

int iosMcGetDir(int port, int verbose, int a, int b, int c, int d, int e2)
{
    unsigned int i;
    int code;
    int ret;
    McErr *e;

    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    code = sceMc2GetDir(B_0004F804[port].port, a, b, c, d, e2) & 0xFFFF;
    ret = 8;
    e = D_000406E8;
    i = 0;
    do {
        if (code == e->code) {
            ret = e->ret;
            break;
        }
        i++;
        e++;
    } while (i < 0x16);
    return ret;
}

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
