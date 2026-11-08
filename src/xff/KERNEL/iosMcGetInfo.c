typedef struct { int pad0; int port; char pad8[0x20]; } McPort;
typedef struct { int code; int result; int pad; } McError;
extern McPort B_0004F800[];
extern McError D_000406E8[];
extern char RO_000424F0[];
extern void LoaderSysPrintf(const char *, ...);
extern int sceMc2GetInfo(int, int *);

#ifdef NONMATCHING
/* Parked: 48 words differ (retry movn and lookup loop layout) */
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
            if (r != prev) {
                prev = r;
                retry = 8;
            }
            break;
        }
    } while (--retry > 0);
    ret = 8;
    e = D_000406E8;
    for (i = 0; i < 22; i++, e++) {
        if (r == e->code) {
            ret = e->result;
            break;
        }
    }
    return ret;
}
#endif
