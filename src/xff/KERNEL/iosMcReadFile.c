typedef struct { int port; char pad[0x24]; } McPort;
typedef struct { int code; int ret; int pad; } McErr;
extern McPort B_0004F804[];
extern McErr D_000406E8[];
extern char RO_000424F0[];
extern void LoaderSysPrintf(const char *, ...);
extern int sceMc2ReadFile(int, int, int, int, int);

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
