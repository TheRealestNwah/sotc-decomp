extern int sceRmdir(const char *name);

int LoaderSysRmdir(const char *name) {
    return sceRmdir(name);
}
