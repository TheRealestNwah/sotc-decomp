extern void Sg2RemoteSend(int, int, int, int);

int Sg2StAdpcmQuit(void)
{
    Sg2RemoteSend(0x17, 0, 0, 0);
    return 0;
}
