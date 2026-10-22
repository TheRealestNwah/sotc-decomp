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
extern int LoaderSysFClose(int);
extern int LoaderSysFRead(int, void *, int);
extern int LoaderSysGetstat(char *, LoaderStat *);

static inline FileEnt *file_find(int fd)
{
    int i;
    FileEnt *p;
    for (i = 0; i < 8; i++) {
        if (B_000543A8[i].fd == fd)
            goto found;
    }
    return 0;
found:
    return &B_000543A8[i];
}

static inline int file_open(char *name)
{
    LoaderStat st;
    FileEnt *e;
    int fd;

    fd = LoaderSysFOpen(name, 1, 0);
    if (fd < 0)
        return fd;
    {
        e = file_find(-1);
        e->fd = fd;
        LoaderSysGetstat(name, &st);
        e->size = st.size;
    }
    return fd;
}

static inline int file_size(int fd)
{
    FileEnt *e = file_find(fd);
    if (e)
        return e->size;
    return 0;
}

static inline void file_close(int fd)
{
    int i;
    LoaderSysFClose(fd);
    for (i = 0; i < 8; i++) {
        if (B_000543A8[i].fd == fd)
            goto found;
    }
    __asm__ volatile("break 0");
    return;
found:
    B_000543A8[i].fd = -1;
}

extern int iosLoaderGetFileSizeName(char *);

int iosFileRead(char *name, void *buf, int max)
{
    int size;
    int fd;

    size = iosLoaderGetFileSizeName(name);
    fd = file_open(name);
    if (fd < 0)
        return -1;
    if (size <= max)
        LoaderSysFRead(fd, buf, size);
    else
        LoaderSysFRead(fd, buf, max);
    file_close(fd);
    return size;
}
