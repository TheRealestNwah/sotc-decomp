extern int Sg2RemoteSend(int, int, int, int);

int Sg2StAdpcmStop(unsigned long id)
{
    if (id != 0)
        Sg2RemoteSend(0x1D, id & 0xFFFFFF, (id >> 24) & 0xFFFFFF, 0);
    return 0;
}
