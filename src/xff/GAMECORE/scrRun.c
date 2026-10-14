extern int isysGetThisSubThread();
extern int func_00095428();

int scrRun(void)
{
    return func_00095428(isysGetThisSubThread());
}
