extern int D_0013C790[256];

static inline int find(int addr) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013C790[i] == addr) {
            return i;
        }
    }
    return -1;
}

int LoaderSysEntryExternalIopMemoryList(int addr) {
    int i;

    if (addr != 0) {
        i = find(0);
        if (i >= 0) {
            D_0013C790[i] = addr;
            return i;
        }
    }
    return -1;
}
