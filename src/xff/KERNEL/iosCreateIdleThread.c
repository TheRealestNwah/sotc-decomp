extern char B_0004E5B0[];
extern char B_0004E5D0[];
extern int *B_0004F5D0;
extern void func_00000910();
extern void iosCreateMsgQueue(void *, int, int);
extern int *iosCreateThread(void *, void *, int, int, int);
extern int iosStartThread(int *, void *);

int iosCreateIdleThread(void)
{
    iosCreateMsgQueue(B_0004E5B0, 0, 0);
    B_0004F5D0 = iosCreateThread(func_00000910, B_0004E5D0, 0x1000, 0x7D, 0);
    return iosStartThread(B_0004F5D0, 0);
}
