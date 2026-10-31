extern int D_00040D6C;
extern volatile int D_00040D64;
extern unsigned long B_000BF6D0;
extern unsigned long iosGetTCountExtension(void);

static int func_0001B850(int cnt)
{
    int r;

    if (D_00040D6C == 0) {
        r = 0;
        if (cnt == D_00040D64 && (float)(iosGetTCountExtension() - B_000BF6D0) < 2124999.75f)
            r = 1;
    } else {
        r = 1;
    }
    return r;
}
