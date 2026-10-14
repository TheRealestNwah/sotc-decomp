extern void Sg2RemoteSend(int, int, int, int);

int Sg2StPcmQuit(void)
{
    Sg2RemoteSend(0x1F, 0, 0, 0);
    return 0;
}
