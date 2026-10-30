extern int iosLoaderFOpen(void *, int, int);
extern int iosLoaderFRead();
extern int iosLoaderFClose(int fd);

static int func_0000A1A8(int buf, void *name, int size)
{
    int fd = iosLoaderFOpen(name, 1, 0);
    iosLoaderFRead(fd, buf, size);
    return iosLoaderFClose(fd);
}
