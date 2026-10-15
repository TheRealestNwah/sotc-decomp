extern void func_0004B128(void *arg);
extern int isysJumpSubThread();

static int func_0004B048(int a, int b, int c, int d)
{
    return isysJumpSubThread((int)func_0004B128, a, c, d);
}
