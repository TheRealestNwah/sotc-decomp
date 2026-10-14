extern void Sg2RemoteSend(int, int, int, int);

int Sg2StAdpcmInit(void)
{
    Sg2RemoteSend(0x16, 0, 0, 0);
    return 0;
}
