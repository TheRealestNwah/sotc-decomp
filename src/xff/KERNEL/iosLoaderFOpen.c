typedef struct {
    int fd;
    int size;
} FileEnt;

typedef struct {
    int unk0;
    int unk4;
    int size;
    char pad[0x34];
} LoaderStat;

extern FileEnt B_000543A8[8];
extern int LoaderSysFOpen(char *, int, int);
extern int LoaderSysGetstat(char *, LoaderStat *);

static inline FileEnt *file_find(int fd)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (B_000543A8[i].fd == fd)
            goto found;
    }
    return 0;
found:
    return &B_000543A8[i];
}

int iosLoaderFOpen(char *name, int flags, int mode)
{
    LoaderStat st;
    FileEnt *e;
    int fd;

    fd = LoaderSysFOpen(name, flags, mode);
    if (fd < 0)
        return fd;
    e = file_find(-1);
    e->fd = fd;
    LoaderSysGetstat(name, &st);
    e->size = st.size;
    return fd;
}
