extern void *memset(void *s, int c, unsigned int n);
extern int D_0013A07C;
extern void (*D_0013CFA0[10])(void);

void loaderExecResetCallback(void) {
    int i;

    for (i = 0; i < 10; i++) {
        if (D_0013CFA0[i] != 0) {
            D_0013CFA0[i]();
        }
    }
    memset(D_0013CFA0, 0, sizeof(D_0013CFA0));
    D_0013A07C = 0;
}
