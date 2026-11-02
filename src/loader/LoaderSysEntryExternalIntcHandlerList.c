struct IntcHandler {
    int cause;
    int id;
};

extern struct IntcHandler D_0013BF90[256];

static inline int findFree(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BF90[i].id < 0) {
            return i;
        }
    }
    return -1;
}

void LoaderSysEntryExternalIntcHandlerList(int id, int cause) {
    int i = findFree();

    D_0013BF90[i].id = id;
    D_0013BF90[i].cause = cause;
}
