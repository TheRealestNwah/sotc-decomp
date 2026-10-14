extern int Sg2SmfpOpenSelCore();

int Sg2SmfpOpen(int a, int b, int c, int d)
{
    return Sg2SmfpOpenSelCore(a, b, 2, d);
}
