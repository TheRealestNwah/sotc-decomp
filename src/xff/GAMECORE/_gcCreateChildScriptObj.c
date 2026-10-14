extern int createScriptObj();

int _gcCreateChildScriptObj(int a, int b, int c, int d, int e, int f, int g, int h)
{
    return createScriptObj(a, b, c, d, e, f, h, 0);
}
