extern void *func_00008BB0(const char *, int, void *);
extern int iosLoaderGetFileSizeName(const char *);
void *loadtest(const char *path, void *partition)
{
    int size;
    void *module;
    size = iosLoaderGetFileSizeName(path);
    module = 0;
    if (size >= 0)
        module = func_00008BB0(path, size, partition);
    return module;
}
