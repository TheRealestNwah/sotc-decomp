extern int sceClose(int fd);

int LoaderSysFClose(int fd) {
    return sceClose(fd);
}
