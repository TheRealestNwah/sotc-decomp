extern int D_0013B790[256];

static inline int findFree(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013B790[i] < 0) {
            return i;
        }
    }
    return -1;
}

void LoaderSysEntryExternalThreadList(int id) {
    D_0013B790[findFree()] = id;
}
