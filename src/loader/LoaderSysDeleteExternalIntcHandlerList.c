struct IntcHandler {
    int cause;
    int id;
};

extern struct IntcHandler D_0013BF90[256];

int LoaderSysDeleteExternalIntcHandlerList(int id) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BF90[i].id == id) {
            D_0013BF90[i].id = -1;
            D_0013BF90[i].cause = -1;
            return id;
        }
    }
    return -1;
}
