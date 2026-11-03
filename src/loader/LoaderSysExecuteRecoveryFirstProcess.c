extern int GetThreadId(void);
extern int ChangeThreadPriority(int thread, int priority);
extern int TerminateThread(int thread);
extern int DeleteThread(int thread);
extern void LoaderSysDeleteAllExternalIntcHandler(void);
extern void LoaderSysDeleteAllExternalSema(void);
extern void LoaderSysFlushPrint(void);
extern int sceSifInitRpc(unsigned int mode);
extern int sceSifInitIopHeap(void);
extern int sceSifFreeIopHeap(void *addr);
extern int D_0013B790[256];
extern int D_0013C790[256];

void LoaderSysExecuteRecoveryFirstProcess(void) {
    ChangeThreadPriority(GetThreadId(), 1);
    LoaderSysDeleteAllExternalIntcHandler();
    {
        int me = GetThreadId();
        int i;

        for (i = 0; i < 256; i++) {
            if (D_0013B790[i] != me && D_0013B790[i] >= 0) {
                ChangeThreadPriority(D_0013B790[i], 0x7F);
            }
        }
    }
    {
        int me = GetThreadId();
        int i;

        for (i = 0; i < 256; i++) {
            if (D_0013B790[i] != me && D_0013B790[i] >= 0) {
                TerminateThread(D_0013B790[i]);
                DeleteThread(D_0013B790[i]);
                D_0013B790[i] = -1;
            }
        }
    }
    LoaderSysDeleteAllExternalSema();
    LoaderSysFlushPrint();
    {
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
}
