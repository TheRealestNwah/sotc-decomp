extern int D_0013B790[256];

void LoaderSysExternalThreadListCallBack(void (*callback)(int thread)) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013B790[i] != -1) {
            callback(D_0013B790[i]);
        }
    }
}
