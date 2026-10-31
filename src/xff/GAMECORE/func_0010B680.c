extern void _resetBaseMoveWork(int a, char *p);
extern void func_0010B6B0(char *p);

static void func_0010B680(int a, char *p)
{
    _resetBaseMoveWork(a, p);
    *(int *)(p + 0x30) = 0;
    func_0010B6B0(p);
}
