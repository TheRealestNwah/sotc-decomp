extern void isysJumpSubThread(void (*)(void), void *);
extern void func_0004AA98(void);

static void func_0004B090(void *arg)
{
    isysJumpSubThread(func_0004AA98, arg);
}
