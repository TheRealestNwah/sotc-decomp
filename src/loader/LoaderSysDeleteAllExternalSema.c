struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};

extern int DeleteSema(int sema_id);
extern int ReferSemaStatus(int sema_id, struct SemaParam *param);
extern int D_0013BB90[256];
extern unsigned int D_00131F80[3];

static inline void initList(void) {
    int i;
    int value = -1;

    for (i = 255; i >= 0; i--) {
        D_0013BB90[i] = value;
    }
}

static inline int isLoaderSema(int id) {
    struct SemaParam param;
    int j;

    if (ReferSemaStatus(id, &param) == id) {
        for (j = 0; j < 3; j++) {
            if (D_00131F80[j] == param.attr) {
                return 1;
            }
        }
    }
    return 0;
}

void LoaderSysDeleteAllExternalSema(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BB90[i] >= 0) {
            DeleteSema(D_0013BB90[i]);
            D_0013BB90[i] = -1;
        }
    }
    initList();
    for (i = 0; i < 256; i++) {
        if (isLoaderSema(i)) {
            DeleteSema(i);
        }
    }
}
