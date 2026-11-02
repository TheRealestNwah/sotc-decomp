extern int GetThreadId(void);
extern int ChangeThreadPriority(int thread, int priority);
extern int D_0013B790[256];

void LoaderSysChangeExteranalThreadPriorityExceptMe(int priority) {
    int me = GetThreadId();
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013B790[i] != me && D_0013B790[i] >= 0) {
            ChangeThreadPriority(D_0013B790[i], priority);
        }
    }
}
