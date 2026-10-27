extern void *isysGetThisSubThread(void);
extern void func_00095428(void *thread);

void scrRun(void)
{
    func_00095428(isysGetThisSubThread());
}
