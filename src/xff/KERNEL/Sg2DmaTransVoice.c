extern int Sg2RemoteSendDmaCom(int, int, int, int);

int Sg2DmaTransVoice(int a, int b, int c)
{
    return Sg2RemoteSendDmaCom(0x13, a, b, c);
}
