extern void Sg2RemoteSend(int, int, int, int);

int Sg2StPcmSetEffect(int a)
{
    Sg2RemoteSend(0x23, a, 0, 0);
    return 0;
}
