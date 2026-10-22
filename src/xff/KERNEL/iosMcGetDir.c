typedef struct { int port; char pad[0x24]; } McPort;
typedef struct { int code; int ret; int pad; } McErr;
extern McPort B_0004F804[];
extern McErr D_000406E8[];
extern char RO_000424F0[];
extern void LoaderSysPrintf(const char *, ...);
extern int sceMc2GetDir(int, int, int, int, int, int);

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
