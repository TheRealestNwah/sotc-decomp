extern int func_0002EA68(int);
extern int func_0002EAB8(int, int);
extern void func_0002E8D8(int, int, int, int);

int Sg2ExPcmOutputSetAutoFilter(int a, int b)
{
    int n = func_0002EA68(a);
    if (n == -1)
        return n;
    if (!(b < n))
        return -2;
    func_0002E8D8(func_0002EAB8(a, b), 5, a, b);
    return 0;
}
