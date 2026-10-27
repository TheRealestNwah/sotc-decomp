typedef void (*ResetCallback)(void);
extern ResetCallback B_0004F5F0[];
extern char RO_00041FE0[];
extern void loaderSetResetCallback(ResetCallback);
extern void iosJumpRecoverPoint(void *, ...);
static void func_00000F28(void);

void iosLoaderResetEntry(ResetCallback fn)
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

static void func_00000F28(void)
{
    ResetCallback *next = B_0004F5F0;
    int remaining;
    for (remaining = 1; remaining >= 0; remaining--) {
        ResetCallback callback = *next++;
        if (callback != 0)
            callback();
    }
}
