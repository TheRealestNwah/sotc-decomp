struct IntcHandler {
    int cause;
    int id;
};

extern struct IntcHandler D_0013BF90[256];

void LoaderSysInitExternalIntcHandlerList(void) {
    int i;

    for (i = 0; i < 256; i++) {
        D_0013BF90[i].id = -1;
        D_0013BF90[i].cause = -1;
    }
}
