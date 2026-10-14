extern int Sg2RemoteDmaTransStatus();

int Sg2DmaTransStatus(int a, int b, int c, int d)
{
    return Sg2RemoteDmaTransStatus(a, b, c, d);
}
