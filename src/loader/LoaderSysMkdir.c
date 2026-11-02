extern int sceMkdir(const char *name, int mode);

int LoaderSysMkdir(const char *name, int mode) {
    return sceMkdir(name, mode);
}
