extern int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StPcmSetVolume(int ch, int vol)
{
    Sg2RemoteSend(0x22, ch, vol, 0);
    return 0;
}
