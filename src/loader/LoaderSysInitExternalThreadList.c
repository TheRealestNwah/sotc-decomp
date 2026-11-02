extern int D_0013B790[256];

void LoaderSysInitExternalThreadList(void) {
    int i;
    int value = -1;

    for (i = 255; i >= 0; i--) {
        D_0013B790[i] = value;
    }
}
