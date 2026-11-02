extern void PutString(int attr, const char *format, ...);
extern void PutStringS(int attr, const char *format, ...);
extern int sceSifSearchModuleByName(const char *name);
extern int sceSifStopModule(int id, int argc, const char *args, int *result);
extern int sceSifUnloadModule(int id);
extern char D_00136B48[];
extern char D_00136B58[];
extern char D_0013A018[];
extern char D_0013A020[];
extern char D_0013A028[];
extern char D_0013A030[];

int LoaderSysUnloadIopModuleByName(const char *name, int unused1, int unused2, int *result) {
    int dummy;
    int id;
    int ret;

    PutString(0x4080FF00, D_00136B48);
    PutString(0x80C0FF00, D_0013A018, name);
    PutStringS(0x4080FF00, D_0013A020);
    id = sceSifSearchModuleByName(name);
    if (id >= 0) {
        ret = sceSifStopModule(id, 1, D_0013A030, result ? result : &dummy);
        if (ret < 0) {
            goto error;
        }
        ret = sceSifUnloadModule(id);
    } else {
        ret = id;
    }
    if (ret < 0) {
    error:
        PutStringS(0xFF804000, D_00136B58, name, ret);
        return -1;
    }
    PutStringS(0x4080FF00, D_0013A028);
    return ret;
}
