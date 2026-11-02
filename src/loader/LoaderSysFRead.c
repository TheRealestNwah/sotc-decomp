extern int sceRead(int fd, void *buf, int size);

int LoaderSysFRead(int fd, void *buf, int size) {
    return sceRead(fd, buf, size);
}
