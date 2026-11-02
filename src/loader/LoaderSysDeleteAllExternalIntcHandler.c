struct IntcHandler {
    int cause;
    int id;
};

extern int DisableIntc(int cause);
extern int RemoveIntcHandler(int cause, int id);
extern struct IntcHandler D_0013BF90[256];

static inline void initList(void) {
    int i;

    for (i = 0; i < 256; i++) {
        D_0013BF90[i].id = -1;
        D_0013BF90[i].cause = -1;
    }
}

void LoaderSysDeleteAllExternalIntcHandler(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BF90[i].id >= 0) {
            DisableIntc(D_0013BF90[i].cause);
            RemoveIntcHandler(D_0013BF90[i].cause, D_0013BF90[i].id);
            D_0013BF90[i].id = -1;
            D_0013BF90[i].cause = -1;
        }
    }
    initList();
}
