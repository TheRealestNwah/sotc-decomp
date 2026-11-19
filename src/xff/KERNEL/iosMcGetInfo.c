typedef struct { int pad0; int port; char pad8[0x20]; } McPort;
typedef struct { int code; int result; int pad; } McError;
extern McPort B_0004F800[];
extern McError D_000406E8[];
extern char RO_000424F0[];
extern void LoaderSysPrintf(const char *, ...);
extern int sceMc2GetInfo(int, int *);

int iosMcGetInfo(int port, int verbose, int *out)
{
    int buf[4];
    int r;
    int prev;
    int retry;
    McPort *p;
    McError *e;
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
            ret = e->result;
            break;
        }
        i++;
        e++;
    } while (i < 22);
    return ret;
}
