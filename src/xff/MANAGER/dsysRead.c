extern int LoaderSysFRead(int, void *, int);
extern void iosJumpRecoverPoint(void *);
extern unsigned char RO_001416B0[];

int dsysRead(void *arg0, void *buffer, int size) {
    int var_s0;

    var_s0 = -1;
    if ((*(int *)((char *)(arg0) + 4)) == 0) {
        var_s0 = LoaderSysFRead((*(int *)((char *)(arg0) + 0)), buffer, size);
    } else {
        iosJumpRecoverPoint(RO_001416B0);
    }
    return var_s0;
}
