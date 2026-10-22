extern void Sg2RemoteSend(int, int, int, int);

int Sg2StPcmInit(int unused)
{
    Sg2RemoteSend(0x1E, 0, 0, 0);
    return 0;
}
