typedef struct { int port; char pad[0x24]; } McPort;
extern McPort B_0004F804[];
extern char RO_000424F0[];
extern void LoaderSysPrintf(const char *, ...);
extern int sceMc2Format(int);

int iosMcFormat(int port, int verbose)
{
    if (verbose)
        LoaderSysPrintf(RO_000424F0);
    return sceMc2Format(B_0004F804[port].port);
}
