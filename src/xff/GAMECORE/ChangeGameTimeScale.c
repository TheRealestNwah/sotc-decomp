extern char gcGlobalVar[];
extern int func_0000BB50();

int ChangeGameTimeScale(int a)
{
    *(int *)(gcGlobalVar + 0x198) = a;
    return func_0000BB50();
}
