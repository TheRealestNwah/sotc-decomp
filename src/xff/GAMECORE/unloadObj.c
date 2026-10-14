extern int isysRequestDeleteObj();

int unloadObj(int a, int b, int c, int d)
{
    return isysRequestDeleteObj(a, b, c, d);
}
