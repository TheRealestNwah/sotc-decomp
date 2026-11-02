extern int printf(const char *format, ...);
extern char D_00139FF8[];

int LoaderSysPutString(const char *s) {
    return printf(D_00139FF8, s);
}
