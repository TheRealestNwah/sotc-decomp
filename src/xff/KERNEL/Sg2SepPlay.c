extern int Sg2SepPlaySelectCore();

int Sg2SepPlay(int a, int b, int c, int d)
{
    return Sg2SepPlaySelectCore(a, b, c, d, 2);
}
