extern void Sg2RemoteSend(int, int, int, int);

int Sg2StAdpcmClose(int a)
{
    Sg2RemoteSend(0x19, a, 0, 0);
    return 0;
}
