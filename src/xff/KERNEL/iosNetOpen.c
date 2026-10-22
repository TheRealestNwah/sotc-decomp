extern int D_000407F0;
extern int B_0004F880;
extern int B_000508A8;
extern unsigned char B_00050880[];
extern int func_00004A20(const char *);
extern unsigned int strlen(const char *);
extern char *strncpy(char *, const char *, unsigned int);
extern int WaitSema(int);
extern int SignalSema(int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int,
                         void (*)(void *), void *);

int iosNetOpen(const char *name)
{
    int result;
    if (D_000407F0) {
        result = func_00004A20(name);
    } else {
        int length = strlen(name);
        B_0004F880 = length + 1;
        strncpy((char *)&B_0004F880 + 4, name, length + 1);
        length += 5;
        WaitSema(B_000508A8);
        sceSifCallRpc(B_00050880, 0, 0, &B_0004F880, length,
                      &B_0004F880, 4, 0, 0);
        SignalSema(B_000508A8);
        result = B_0004F880;
    }
    return result;
}
