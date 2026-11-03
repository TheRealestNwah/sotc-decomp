struct NetcnfifArg {
    int data;
    int f_no_decode;
    int type;
    int addr;
    char unk10[0x300];
};

extern int printf(const char *format, ...);
extern int LoaderSysLoadIopModule(const char *path, int argc, const char *argv);
extern void setNewIopIdentifier(const char *name);
extern void FlushCache(int mode);
extern void sceNetcnfifSetup(void);
extern void sceNetcnfifAllocWorkarea(int size);
extern int sceNetcnfifCheck(void);
extern void sceNetcnfifGetResult(struct NetcnfifArg *result);
extern void sceNetcnfifSetFNoDecode(int f_no_decode);
extern void sceNetcnfifLoadEntry(const char *fname, int type, const char *usr_name, void *e);
extern void sceNetcnfifGetAddr(void);
extern int sceNetcnfifSendIOP(void *data, int addr, int size);
extern int sceNetcnfifDmaCheck(int id);
extern void sceNetcnfifSetEnv(int type);
extern int sceInetCtlSetAutoMode(void *cd, void *net_buf, int f_on);
extern int sceLibnetSetConfiguration(void *cd, void *net_buf, int env_addr);
extern char D_00136FB8[];
extern char D_00136FD8[];
extern char D_00137008[];

int func_00104428(void *cd, void *net_buf, void *e, const char *fname, const char *usr_name, int flags) {
    struct NetcnfifArg if_arg;
    int id;
    int ret;
    int addr;

    printf(D_00137008, fname);
    if (flags & 4) {
        if (LoaderSysLoadIopModule(D_00136FB8, 0, 0) < 0) {
            return -1;
        }
        setNewIopIdentifier(D_00136FD8);
    }
    sceNetcnfifSetup();
    sceNetcnfifAllocWorkarea(0x1000);
    {
        struct NetcnfifArg *p = &if_arg;

        while (sceNetcnfifCheck()) {
        }
        sceNetcnfifGetResult(p);
        if (p->data < 0) {
            return -0x21C;
        }
    }
    if (flags & 1) {
        sceNetcnfifSetFNoDecode(0);
    } else {
        sceNetcnfifSetFNoDecode(1);
    }
    FlushCache(0);
    sceNetcnfifLoadEntry(fname, 0, usr_name, e);
    {
        struct NetcnfifArg *p = &if_arg;

        while (sceNetcnfifCheck()) {
        }
        sceNetcnfifGetResult(p);
        ret = p->data;
        if (ret < 0) {
            return -0x21C;
        }
    }
    sceNetcnfifGetAddr();
    {
        struct NetcnfifArg *p = &if_arg;

        while (sceNetcnfifCheck()) {
        }
        sceNetcnfifGetResult(p);
        if (p->data < 0) {
            return -0x21C;
        }
    }
    id = sceNetcnfifSendIOP(e, if_arg.addr, 0x1340);
    if (id == 0) {
        return -0x21C;
    }
    while (sceNetcnfifDmaCheck(id)) {
    }
    sceNetcnfifSetEnv(0);
    {
        struct NetcnfifArg *p = &if_arg;

        while (sceNetcnfifCheck()) {
        }
        sceNetcnfifGetResult(p);
        if (p->data < 0) {
            return -0x21C;
        }
    }
    addr = if_arg.addr;
    if (flags & 2) {
        ret = sceInetCtlSetAutoMode(cd, net_buf, 1);
    } else {
        ret = sceInetCtlSetAutoMode(cd, net_buf, 0);
    }
    if (ret < 0) {
        return ret;
    }
    ret = sceLibnetSetConfiguration(cd, net_buf, addr);
    if (ret < 0) {
        return ret;
    }
    return 0;
}
