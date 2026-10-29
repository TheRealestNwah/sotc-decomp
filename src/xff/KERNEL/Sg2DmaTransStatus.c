extern int Sg2RemoteDmaTransStatus(int);
int Sg2DmaTransStatus(int channel)
{
    return Sg2RemoteDmaTransStatus(channel);
}
