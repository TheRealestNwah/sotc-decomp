extern void *B_0004F5F0[];
extern char RO_00041FE0[];
extern void loaderSetResetCallback(void *);
extern void iosJumpRecoverPoint(void *, ...);
static void func_00000F28(void);

void iosLoaderResetEntry(void *fn)
{
    int i;

    if (B_0004F5F0[0] == 0) {
        loaderSetResetCallback(func_00000F28);
    }
    for (i = 0; i < 2; i++) {
        if (B_0004F5F0[i] == 0) {
            goto found;
        }
    }
    iosJumpRecoverPoint(RO_00041FE0);
found:
    B_0004F5F0[i] = fn;
}
