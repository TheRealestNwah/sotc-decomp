extern int isysRequestDeleteObj();

int lineObjectDelete(int a, int b, int c, int d)
{
    return isysRequestDeleteObj(a, b, c, d);
}
