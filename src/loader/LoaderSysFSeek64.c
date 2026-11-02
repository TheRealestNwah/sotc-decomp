extern long sceLseek64(int fd, long offset, int whence);

long LoaderSysFSeek64(int fd, long offset, int whence) {
    return sceLseek64(fd, offset, whence);
}
