extern int D_0013BB90[256];

static inline int findFree(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BB90[i] < 0) {
            return i;
        }
    }
    return -1;
}

void LoaderSysEntryExternalSemaList(int id) {
    D_0013BB90[findFree()] = id;
}
