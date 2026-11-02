extern int sceOpen(const char *name, int flags, ...);

int LoaderSysFOpen(const char *name, int flags) {
    return sceOpen(name, flags);
}
