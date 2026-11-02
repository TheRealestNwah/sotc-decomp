extern int sceWrite(int fd, const void *buf, int size);

int LoaderSysFWrite(int fd, const void *buf, int size) {
    return sceWrite(fd, buf, size);
}
