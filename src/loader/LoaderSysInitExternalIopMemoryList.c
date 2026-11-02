extern int D_0013C790[256];

void LoaderSysInitExternalIopMemoryList(void) {
    int i;

    for (i = 255; i >= 0; i--) {
        D_0013C790[i] = 0;
    }
}
