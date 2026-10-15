extern char B_0019B870[];
extern void func_000B53E0(void *, int, int);

void initSmallManager(void)
{
    char *m = B_0019B870;
    func_000B53E0(m, 10, 0);
    func_000B53E0(m + 0x9E0, 20, 1);
    *(int *)(m + 0x13CC) = 0;
    *(int *)(m + 0x13D0) = 1;
}
