extern int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StPcmStart(int ch, int arg)
{
    Sg2RemoteSend(0x20, ch, arg, 0);
    return 0;
}
