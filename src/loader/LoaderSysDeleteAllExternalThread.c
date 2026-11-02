extern int TerminateThread(int thread);
extern int DeleteThread(int thread);
extern int D_0013B790[256];

void LoaderSysDeleteAllExternalThread(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013B790[i] >= 0) {
            TerminateThread(D_0013B790[i]);
            DeleteThread(D_0013B790[i]);
            D_0013B790[i] = -1;
        }
    }
}
