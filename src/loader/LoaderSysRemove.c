extern int sceRemove(const char *name);

int LoaderSysRemove(const char *name) {
    return sceRemove(name);
}
