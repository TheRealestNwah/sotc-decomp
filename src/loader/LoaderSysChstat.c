struct sce_stat;
extern int sceChstat(const char *name, struct sce_stat *buf, unsigned int cbit);

int LoaderSysChstat(const char *name, struct sce_stat *buf, unsigned int cbit) {
    return sceChstat(name, buf, cbit);
}
