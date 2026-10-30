extern const char RO_0013B1F0[];
extern unsigned int strlen(const char *);
extern int iosSPrintf(char *, const char *, ...);
extern int LoaderSysFOpen(char *, int, int);

static int func_000DDE48(int *fd, const char *name, int mode)
{
    char path[strlen(name) + 7];

    iosSPrintf(path, RO_0013B1F0 + 0x6468, name);
    *fd = LoaderSysFOpen(path, mode, 0x1FF);
    if (*fd < 0)
        return -1;
    return 0;
}
