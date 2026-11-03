struct sce_stat {
    unsigned int st_mode;
    unsigned int st_attr;
    unsigned int st_size;
    unsigned char st_ctime[8];
    unsigned char st_atime[8];
    unsigned char st_mtime[8];
    unsigned int st_hisize;
    unsigned int st_private[6];
};

extern int LoaderSysGetstat(const char *name, struct sce_stat *buf);
extern int LoaderSysFOpen(const char *name, int flags, int mode);
extern int LoaderSysFRead(int fd, void *buf, int size);
extern int LoaderSysFClose(int fd);
extern void PutStringS(int attr, const char *format, ...);
extern int sscanf(const char *str, const char *format, ...);
struct Info { char buf[0x40]; int val; };
extern struct Info D_00131C00;
extern int D_00131C40[];
extern char D_001364D0[];
extern char D_00139E60[];

char *func_001013C8(const char *name) {
    struct sce_stat st;
    unsigned long size;
    int i;
    int ret;
    struct Info *info = &D_00131C00;

    D_00131C00.val = 0x4000;
    ret = LoaderSysGetstat(name, &st);
    if (ret != 0) {
        PutStringS(0xFF804000, D_001364D0, name, ret);
        return 0;
    }
    ret = LoaderSysFOpen(name, 1, 0);
    if (ret < 0) {
        D_00131C00.buf[0] = 0;
        PutStringS(0xFF804000, D_001364D0, name, ret);
        return 0;
    }
    size = ((unsigned long)st.st_hisize << 32) | st.st_size;
    LoaderSysFRead(ret, D_00131C00.buf, (int)size);
    LoaderSysFClose(ret);
    D_00131C00.buf[(int)size] = 0;
    info->buf[0x3F] = 0;
    for (i = 0; i < size; i++) {
        if (info->buf[i] == ' ') {
            info->buf[i] = 0;
            sscanf(&info->buf[i + 1], D_00139E60, D_00131C40);
            break;
        }
    }
    return D_00131C00.buf;
}

