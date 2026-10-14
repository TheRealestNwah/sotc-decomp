extern void Sg2RemoteSend(int, int, int, int);

int Sg2ChipSetDigitalOutputMode(int m)
{
    Sg2RemoteSend(5, 1, m, 0);
    return 0;
}
