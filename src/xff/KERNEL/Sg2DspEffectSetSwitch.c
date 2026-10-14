extern int Sg2RemoteSend();

int Sg2DspEffectSetSwitch(int a, int b, int c, int d)
{
    return Sg2RemoteSend(9, 0, a, b);
}
