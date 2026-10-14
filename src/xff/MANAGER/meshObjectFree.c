extern int isysRequestDeleteObj();

int meshObjectFree(int a, int b, int c, int d)
{
    return isysRequestDeleteObj(a, b, c, d);
}
