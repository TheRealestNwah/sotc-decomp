extern void PutString(int attr, const char *format, ...);
extern void PutStringS(int attr, const char *format, ...);
extern int sceSifLoadModule(const char *path, int argsLen, const char *args);
extern char D_00136B00[];
extern char D_00136B10[];
extern char D_0013A018[];
extern char D_0013A020[];
extern char D_0013A028[];

int LoaderSysLoadIopModule(const char *path, int argsLen, const char *args) {
    int ret;

    PutString(0x4080FF00, D_00136B00);
    PutString(0x80C0FF00, D_0013A018, path);
    PutStringS(0x4080FF00, D_0013A020);
    ret = sceSifLoadModule(path, argsLen, args);
    if (ret < 0) {
        PutStringS(0xFF804000, D_00136B10, path, ret);
        return -1;
    }
    PutStringS(0x4080FF00, D_0013A028);
    return 0;
}
