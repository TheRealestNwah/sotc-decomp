extern void func_0000AE38(void *);

static void func_0000B200(void)
{
    register char *ra __asm__("$31");

    func_0000AE38(ra - 8);
}
