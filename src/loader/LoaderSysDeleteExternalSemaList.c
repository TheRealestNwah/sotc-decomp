extern int D_0013BB90[256];

int LoaderSysDeleteExternalSemaList(int id) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BB90[i] == id) {
            D_0013BB90[i] = -1;
            return id;
        }
    }
    return -1;
}
