struct NetIf {
    int unk0;
    int id;
};

extern void PutStringS(int attr, const char *format, ...);
extern int printf(const char *format, ...);
extern void *memalign(unsigned int align, unsigned int size);
extern void free(void *p);
extern int func_00104428(void *cd, void *net_buf, void *e, const char *fname, const char *usr_name, int flags);
extern int sceLibnetWaitGetInterfaceID(void *cd, void *net_buf, int *if_id, int n);
extern int sceInetCtlUpInterface(void *cd, void *net_buf, int id);
extern int sceLibnetWaitGetAddress(void *cd, void *net_buf, int *if_id, int n, void *addr, int flags);
extern char D_00137080[];
extern char D_001370A0[];
extern char D_001370B8[];
extern char D_001370D0[];
extern char D_001370E8[];
extern char D_00137108[];
extern char D_00137128[];
extern char D_00137140[];
extern const char *D_00131FA0[];
extern const char *D_00131FB8[];
extern char D_00131FC0[];
extern char D_0013D000[];
extern struct NetIf D_0013A180;
extern int D_0013A184;

int func_00104668(int mode, int index) {
    const char *usr_name;
    const char *fname;
    int flags = 0;
    void *e;
    int ret;

    if (mode == 0) {
        usr_name = D_00131FA0[index];
        fname = D_00137080;
        PutStringS(0x80FF8000, D_001370A0);
    } else {
        PutStringS(0x8080FF00, D_001370B8);
        fname = D_001370D0;
        usr_name = D_00131FB8[index];
        flags = 1;
    }
    printf(D_001370E8);
    {
        char *cd = D_0013D000;
        char *net_buf = cd + 0x40;

        e = memalign(0x40, 0x1340);
        if (e == 0) {
            ret = -0x21F;
        } else {
            int r = func_00104428(cd, net_buf, e, fname, usr_name, flags);
            free(e);
            ret = r;
        }
    }
    if (ret < 0) {
        printf(D_00137108);
        return 0;
    }
    {
        char *cd = D_0013D000;
        char *net_buf = cd + 0x40;
        int *if_id = &D_0013A180.id;

        ret = sceLibnetWaitGetInterfaceID(cd, net_buf, if_id, 1);
        if (ret < 0) {
            printf(D_00137128);
            return 0;
        }
        sceInetCtlUpInterface(cd, net_buf, D_0013A184);
        if (sceLibnetWaitGetAddress(cd, net_buf, if_id, 1, D_00131FC0, 0) < 0) {
            printf(D_00137140);
            return 0;
        }
    }
    return 1;
}
