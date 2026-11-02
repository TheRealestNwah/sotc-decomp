extern int sceSifInitRpc(unsigned int mode);
extern int sceSifInitIopHeap(void);
extern int sceSifFreeIopHeap(void *addr);
extern int D_0013C790[256];

void LoaderSysDeleteAllExternalIopMemory(void) {
    int i;

    sceSifInitRpc(0);
    sceSifInitIopHeap();
    for (i = 0; i < 256; i++) {
        if (D_0013C790[i] != 0) {
            sceSifFreeIopHeap((void *)D_0013C790[i]);
            D_0013C790[i] = 0;
        }
    }
}
