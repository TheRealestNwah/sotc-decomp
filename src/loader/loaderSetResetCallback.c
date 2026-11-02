extern int LoaderSysPrintf(const char *format, ...);
extern char D_00136D30[];
extern int D_0013A07C;
extern void (*D_0013CFA0[10])(void);

void loaderSetResetCallback(void (*callback)(void)) {
    if (D_0013A07C == 10) {
        LoaderSysPrintf(D_00136D30);
        D_0013A07C = 0;
    }
    D_0013CFA0[D_0013A07C++] = callback;
}
