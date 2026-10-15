extern void isysLaunchModule(char *);
extern void FlushCache(int);

int isysLaunchExecModule(char *m)
{
    int (*f)(char *);
    isysLaunchModule(m);
    f = *(int (**)(char *))(*(char **)(m + 0x1C) + 0x10);
    FlushCache(0);
    FlushCache(2);
    return f(m);
}
