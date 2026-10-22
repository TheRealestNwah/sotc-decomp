extern int D_000407F0;
extern int B_0004F880;
extern int B_000508A8;
extern unsigned char B_00050880[];
extern int func_00004C30(int, int);
extern int WaitSema(int);
extern int SignalSema(int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int,
                         void (*)(void *), void *);

int iosNetClose(int handle)
{
    int result;
    if (D_000407F0) {
        result = func_00004C30(handle, -1);
    } else {
        B_0004F880 = handle;
        WaitSema(B_000508A8);
        sceSifCallRpc(B_00050880, 1, 0, &B_0004F880, 4,
                  &B_0004F880, 4, 0, 0);
        SignalSema(B_000508A8);
        result = B_0004F880;
    }
    return result;
}
