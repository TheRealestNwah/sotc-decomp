extern int rootPtn[];
extern void func_0003F488(void);
extern int createScriptObj(void (*)(void), int, int *, int, int, int, int, int);

static int func_0003F278(int arg, int a1)
{
    if (arg != 0) {
        return createScriptObj(func_0003F488, a1, rootPtn, 0x1800, 0, 4, arg, 0);
    }
}
