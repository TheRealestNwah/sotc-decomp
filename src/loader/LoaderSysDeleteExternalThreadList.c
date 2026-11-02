extern int D_0013B790[256];

int LoaderSysDeleteExternalThreadList(int id) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013B790[i] == id) {
            D_0013B790[i] = -1;
            return id;
        }
    }
    return -1;
}
