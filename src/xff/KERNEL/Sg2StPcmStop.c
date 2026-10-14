extern void Sg2RemoteSend(int, int, int, int);

int Sg2StPcmStop(void)
{
    Sg2RemoteSend(0x21, 0, 0, 0);
    return 0;
}
