extern int D_0013BB90[256];

void LoaderSysInitExternalSemaList(void) {
    int i;
    int value = -1;

    for (i = 255; i >= 0; i--) {
        D_0013BB90[i] = value;
    }
}
