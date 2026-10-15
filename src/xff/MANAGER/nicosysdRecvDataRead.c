extern int D_00139EF0;
extern int func_000DEE30(int, int, int);
int nicosysdRecvDataRead(int a, int b, int c)
{
    if (D_00139EF0 == 0)
        return 0;
    return func_000DEE30(a, b, c);
}
