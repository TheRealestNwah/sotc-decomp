extern int Sg2RemoteSend(int, int, int, int);
int Sg2DspEffectSetSwitch(int first, int second)
{
    return Sg2RemoteSend(9, 0, first, second);
}
