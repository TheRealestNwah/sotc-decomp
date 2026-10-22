typedef struct { int port; char pad[0x24]; } McPort;
typedef struct { int code; int ret; int pad; } McErr;
extern McPort B_0004F804[];
extern McErr D_000406E8[];
extern char RO_000424F0[];
extern void LoaderSysPrintf(const char *, ...);
extern int sceMc2Chdir(int, int, int);

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
