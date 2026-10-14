extern void Sg2RemoteSend(int, int, int, int);

int Sg2ChipInitHot(void)
{
    Sg2RemoteSend(0x11, 1, 0, 0);
    return 0;
}
