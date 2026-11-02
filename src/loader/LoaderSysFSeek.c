extern int sceLseek(int fd, int offset, int whence);

int LoaderSysFSeek(int fd, int offset, int whence) {
    return sceLseek(fd, offset, whence);
}
