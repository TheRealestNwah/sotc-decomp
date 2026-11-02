struct sce_stat;
extern int sceGetstat(const char *name, struct sce_stat *buf);

int LoaderSysGetstat(const char *name, struct sce_stat *buf) {
    return sceGetstat(name, buf);
}
