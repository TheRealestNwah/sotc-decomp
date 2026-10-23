typedef struct {
    int fd;
    int size;
} FileEnt;

extern FileEnt B_000543A8[8];
extern int LoaderSysFClose(int);

int iosLoaderFClose(int fd)
{
    int result = LoaderSysFClose(fd);
    int i;

    for (i = 0; i < 8; i++) {
        if (B_000543A8[i].fd == fd)
            goto found;
    }
    __asm__ volatile("break 0");
    goto end;
found:
    B_000543A8[i].fd = -1;
end:
    return result;
}
