extern char rootPtn[];
extern int iosLoaderFOpen(void *, int, int);
extern int iosLoaderGetFileSize(int);
extern void *iosMallocAlign(void *, int, int);
extern int iosLoaderFRead();
extern int LoaderSysLoadIopModuleFromEEBuffer(void *, void *, int, int, int);
extern void iosFree(void *);
extern int iosLoaderFClose(int);
int iosLoadIopModule(void *path, void *name, int args, int argp)
{
    int fd = iosLoaderFOpen(path, 1, 0);
    int size;
    void *buffer;
    int result;
    if (fd < 0) {
        return -1;
    }
    size = iosLoaderGetFileSize(fd);
    buffer = iosMallocAlign(rootPtn, size, 64);
    iosLoaderFRead(fd, buffer, size);
    result = LoaderSysLoadIopModuleFromEEBuffer(name, buffer, size, args, argp);
    iosFree(buffer);
    iosLoaderFClose(fd);
    return result;
}
