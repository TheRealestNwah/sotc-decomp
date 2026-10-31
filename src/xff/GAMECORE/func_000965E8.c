extern void func_00096610(void);
extern void *isysGetThisSubThread(void);
extern void func_00095428(void *);

static void func_000965E8(void)
{
    for (;;) {
        func_00096610();
        func_00095428(isysGetThisSubThread());
    }
}
